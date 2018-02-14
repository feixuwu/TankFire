/// <reference path="../typings/index.d.ts" />
/// <reference path="../../Common/common.d.ts" />
/// <reference path="../../Common/routerinterface.d.ts" />

import * as fs from 'fs'
import {Config} from './CenterServer'
import {QueueClient, ConnUserInfo} from './QueueClient'
import {AgentManager} from './AgentManager'
import {RequestQueueInfo} from './QueueClient'
import { Buffer } from 'buffer';


var config:Config = JSON.parse(fs.readFileSync("../Config/config.json", "utf8") )

setInterval(()=>{
    ServerManager.processGamePair();
}, 5000)


export interface PairReadyGroup{
    userList:ServerInteface.UserToken[];
}

export interface ConnServerInfo{
    serverKey:string;
}

export class ServerManager{
    
    static fullServerList:{[key:string]:ServerInteface.GameServerStatus} = {}
    static notFullServerList:{[key:string]:ServerInteface.GameServerStatus} = {}
    static readyPairList:{[key:number]:PairReadyGroup[]} = {}
    

    static onReceiveMessage(conn:ServerCommon.IWebSocketConn, data:string){
        try
        {
            var dataObj = JSON.parse(data)
            console.log("~~~~csMsg" + data);
            ServerManager.processMessage(conn, dataObj);
        }
        catch(e)
        {
            console.log("invalid message:" + data)      
        }
    }

    static processMessage(conn:ServerCommon.IWebSocketConn, message:any){
        switch(message.cmd){
            case MessageProto.command.CMD_GS_FETCH_USERTOKEN:
            ServerManager.processGSFetchUserToken(conn, message)
            break;

            case MessageProto.command.CMD_GS_QUERYACCOUNT:
            ServerManager.processGSQueryAccount(conn, message);
            break;

            case MessageProto.command.CMD_GS_UPDATEACCOUNT:
            ServerManager.processGSUpdateAccount(conn, message);
            break;

            case MessageProto.command.CMD_GS_CLOSE:
            ServerManager.removeConn(conn);
            break;
        }
    }


    static processZoneGamePair(zone:number, zoneQueueList:RequestQueueInfo[]){
        
        if(zoneQueueList.length == 0){
            return;
        }

        if(Object.keys(ServerManager.notFullServerList).length > 0){
            var keys = Object.keys(ServerManager.notFullServerList)
            for(var i = 0; i < keys.length; i++){
                if(zoneQueueList.length == 0){
                    return;
                }

                var canPutNum = config.centerServer.gameconfig.maxplayercnt - ServerManager.notFullServerList[keys[i]].userList.length;
                var tmpServer = ServerManager.notFullServerList[keys[i]];

                // only search valid zone
                if(tmpServer.serverInfo.zone != zone){
                    continue;
                }

                for(var j = 0; j < canPutNum; j++){
                    if(zoneQueueList.length == 0){
                        return;
                    }

                    var tmpReq = zoneQueueList[0];
                    zoneQueueList.splice(0, 1)
                    tmpServer.userList.push({
                        strAccount:tmpReq.accountInfo.strAccount,
                        strToken:tmpReq.accountInfo.strToken,
                        headiconurl:tmpReq.accountInfo.headiconurl,
                        strName:tmpReq.accountInfo.strName,
                        connKey:tmpReq.accountInfo.connKey,
                    });

                    // 通知服务器添加新人
                    var scMessage:MessageProto.SC_CMD_GS_ADD_USER = {
                        cmd:MessageProto.command.CMD_GS_ADD_USER,
                        newUser:{
                            account:tmpReq.accountInfo.strAccount,
                            token:tmpReq.accountInfo.strToken,
                            name:tmpReq.accountInfo.strName,
                            headurl:tmpReq.accountInfo.headiconurl,
                        }
                    }
                    ServerManager.sendSCMessage(tmpServer.serverInfo._user, scMessage);

                    // 通知客户端，加入游戏
                    var scClientMsg:MessageProto.SC_CMD_CLIENT_JOIN_GAME = {
                        cmd:MessageProto.command.CMD_CLIENT_JOIN_GAME,
                        host:tmpServer.serverInfo.host,
                        port:tmpServer.serverInfo.port,
                        serverkey:tmpServer.serverInfo.serverKey,
                    }

                    var client = QueueClient.getClient(tmpReq.accountInfo.connKey)
                    QueueClient.sendSCMessage(client, scClientMsg)
                }
                
                // 如果满了，加入到FullList
                if(tmpServer.userList.length >= config.centerServer.gameconfig.maxplayercnt){
                    delete ServerManager.notFullServerList[tmpServer.serverInfo.serverKey];
                    ServerManager.fullServerList[tmpServer.serverInfo.serverKey] = tmpServer;
                }
            }
        }

        // 如果还有人，并且数量超过最少人数，创建一个服务器
        while(zoneQueueList.length >= config.centerServer.gameconfig.minplayercnt){
            var readyGroup:PairReadyGroup = {
                userList:[]
            }
            
            for(var i = 0; i < config.centerServer.gameconfig.maxplayercnt; i++){
                if(zoneQueueList.length == 0){
                    break;
                }

                var tmpReq = zoneQueueList[0];
                zoneQueueList.splice(0, 1)
                
                readyGroup.userList.push({
                    strAccount:tmpReq.accountInfo.strAccount,
                    strToken:tmpReq.accountInfo.strToken,
                    headiconurl:tmpReq.accountInfo.headiconurl,
                    strName:tmpReq.accountInfo.strName,
                    connKey:tmpReq.accountInfo.connKey,
                })
            }

            if(ServerManager.readyPairList[zone] == null){
                ServerManager.readyPairList[zone] = [];
            }
            ServerManager.readyPairList[zone].push(readyGroup);

            // 随机一个Agent，创建Server
            AgentManager.randomCreateServer(zone);
        }
    }

    static processGamePair(){
        var keys = Object.keys(QueueClient.clientQueueList)
        for(var i = 0; i < keys.length; i++){
            var zone = parseInt(keys[i])
            ServerManager.processZoneGamePair(zone, QueueClient.clientQueueList[zone]);
        }
    }

    static processGSUpdateAccount(conn:ServerCommon.IWebSocketConn, message:MessageProto.CS_CMD_GS_UPDATEACCOUNT){
        if(message.accountData == null){
            return;
        }

        var queryString = new Buffer(message.accountData.account).toString("base64")
        var saveString = new Buffer(JSON.stringify(message.accountData) ).toString("base64")

        var redisconn = QueueClient.getRedisConn();
        redisconn.set(queryString, saveString);
    }

    static processGSQueryAccount(conn:ServerCommon.IWebSocketConn, message:MessageProto.CS_CMD_GS_QUERYACCOUNT){
        if(message.accout == null){
            return;
        }

        var scMessage:MessageProto.SC_CMD_GS_QUERYACCOUNT = {
            cmd:MessageProto.command.CMD_GS_QUERYACCOUNT,
            result:MessageProto.enResult.enResult_Fail,
            accountData:{
                account:"",
                name:"",
                cup:0,
                segment:0,
                star:0,
            }
        }

        var rediConn = QueueClient.getRedisConn();
        var queryString = new Buffer(message.accout).toString("base64")
        rediConn.get(queryString, (error, data)=>{
            if(error != null){
                console.log("server query account error:" + error)
                ServerManager.sendSCMessage(conn, scMessage)
                return;
            }

            if(data == null){                
                ServerManager.sendSCMessage(conn, scMessage)
                return;
            }

            var orgData = new Buffer(data, "base64").toString();
            var accoutData:MessageProto.AccountData = JSON.parse(orgData)
            scMessage.result = MessageProto.enResult.enResult_OK;
            scMessage.accountData = accoutData
            ServerManager.sendSCMessage(conn, scMessage)
        })
    }

    static processGSFetchUserToken(conn:ServerCommon.IWebSocketConn, message:MessageProto.CS_CMD_GS_FETCH_USERTOKEN){
        var scMessage:MessageProto.SC_CMD_GS_FETCH_USERTOKEN = {
            cmd:MessageProto.command.CMD_GS_FETCH_USERTOKEN,
            result:MessageProto.enResult.enResult_Fail,
            userList:[],
        }

        if(message.zone == null){
            return;
        }

        var zoneReadyPairList = ServerManager.readyPairList[message.zone]
        if(zoneReadyPairList == null){
            ServerManager.readyPairList[message.zone] = []
            zoneReadyPairList = ServerManager.readyPairList[message.zone]
        }
        if(zoneReadyPairList.length == 0){
            ServerManager.sendSCMessage(conn, scMessage)
            return;
        }

        scMessage.result = MessageProto.enResult.enResult_OK;

        // 添加到游戏List,修改Client的ServerKey参数
        var readyGroup = zoneReadyPairList[0]
        zoneReadyPairList.splice(0, 1)

        var serverStatus:ServerInteface.GameServerStatus = {
            userList:[],
            serverInfo:{
                host:message.host,
                port:message.port,
                serverKey:message.serverKey,
                _user:conn,
                zone:message.zone,
            }
        }

        for(var i = 0; i < readyGroup.userList.length; i++){
            var client = QueueClient.getClient(readyGroup.userList[i].connKey)
            if(client == null || client._user == null){
                continue;
            }
            var connUserInfo:ConnUserInfo = client._user;
            connUserInfo.serverKey = message.serverKey;

            serverStatus.userList.push({
                strAccount:readyGroup.userList[i].strAccount,
                strToken:readyGroup.userList[i].strToken,
                headiconurl:readyGroup.userList[i].headiconurl,
                strName:readyGroup.userList[i].strName,
                connKey:readyGroup.userList[i].connKey,
            })

            scMessage.userList.push({
                account:readyGroup.userList[i].strAccount,
                token:readyGroup.userList[i].strToken,
                name:readyGroup.userList[i].strName,
                headurl:readyGroup.userList[i].headiconurl,
            })

            // 通知客户端，加入游戏
            var scClientMsg:MessageProto.SC_CMD_CLIENT_JOIN_GAME = {
                cmd:MessageProto.command.CMD_CLIENT_JOIN_GAME,
                host:message.host,
                port:message.port,
                serverkey:message.serverKey,
            }

            QueueClient.sendSCMessage(client, scClientMsg)
        }

        if(serverStatus.userList.length >= config.centerServer.gameconfig.maxplayercnt){
            ServerManager.fullServerList[message.serverKey] =serverStatus;
        }
        else{
            ServerManager.notFullServerList[message.serverKey] = serverStatus;
        }

        // 绑定UserInfo
        var serverConnInfo:ConnServerInfo = {
            serverKey:message.serverKey,
        }
        conn._user = serverConnInfo;

        // 通知游戏服
        ServerManager.sendSCMessage(conn, scMessage)
    }

    static sendSCMessage(conn:ServerCommon.IWebSocketConn, data:any){
        conn.send(JSON.stringify(data), null, (error)=>{
            if(error != null){
                return;
            }
        });
    }

    static onClose(conn:ServerCommon.IWebSocketConn, reason:number, desc:string){
        ServerManager.removeConn(conn);
    }

    static OnError(conn:ServerCommon.IWebSocketConn, error:string){
        ServerManager.removeConn(conn);
    }

    static removeConn(conn:ServerCommon.IWebSocketConn){
        var connServerInfo:ConnServerInfo = conn._user
        if(connServerInfo != null){
            if(this.notFullServerList[connServerInfo.serverKey] != null){
                delete this.notFullServerList[connServerInfo.serverKey];
            }
    
            if(this.fullServerList[connServerInfo.serverKey] != null){
                delete this.fullServerList[connServerInfo.serverKey]
            }
        }
        
    }

    static getOwnGame(strAccount:string):ServerInteface.GameServerStatus{
        
        // 遍历
        var result = ServerManager.findOwnGame(ServerManager.notFullServerList, strAccount);
        if(result != null){
            return result;
        }

        result = ServerManager.findOwnGame(ServerManager.fullServerList, strAccount);
        
        return result;
    }

    static findOwnGame(serverList:{[key:string]:ServerInteface.GameServerStatus}, strAccount:string):ServerInteface.GameServerStatus{
        var keys = Object.keys(serverList);
        for(var i = 0; i < keys.length; i++){
            for(var j = 0; j < serverList[keys[i]].userList.length; j++){
                if(serverList[keys[i]].userList[i].strAccount == strAccount){
                    return serverList[keys[i]]
                }
            }
        }

        return null;
    }

    static getKey(conn:ServerCommon.IWebSocketConn):string
    {
        var key = conn._socket.remoteAddress + "_" + conn._socket.remotePort;
        return key;
    }
}