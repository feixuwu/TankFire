/// <reference path="../typings/index.d.ts" />
/// <reference path="../../Common/common.d.ts" />
/// <reference path="../../Common/routerinterface.d.ts" />
/// <reference path="../../Common/MessageProto.d.ts" />

import * as fs from 'fs'
import {QueueClient} from './QueueClient'
import {ServerManager} from './ServerManager'
import {AgentManager} from './AgentManager'
import { debug } from 'util';
require("../../Common/common.js")
require("../../Common/message.js")

export interface ServerConfig{
    host:string;
    port:number;
}

export interface GameConfig{
    maxplayercnt:number;
    minplayercnt:number;
    gametime:number;
}

export interface AgentConfig{
    cmd:string;
    host:string;
    port:string;
}

export interface Config{
    centerServer:{
        forclient:ServerConfig;
        forserver:ServerConfig;
        host:string;
        port:number;
        redishost:string;
        redisport:number;
        gameconfig:GameConfig;
        zonelist:MessageProto.ServerZone[];
    };
    agentServer:AgentConfig
}

var config:Config = JSON.parse(fs.readFileSync("../Config/config.json", "utf8") )
ServerCommon.CreateWebSocketServer(config.centerServer.forclient.host, config.centerServer.forclient.port, {
    OnRequest(conn:ServerCommon.IWebSocketConn, data:string){
        QueueClient.onReceiveMessage(conn, data)
    },

    OnClose(conn:ServerCommon.IWebSocketConn, reason:number, desc:string){
        QueueClient.onClose(conn, reason, desc);
    },

    OnError(conn:ServerCommon.IWebSocketConn, error:string){
        QueueClient.OnError(conn, error);
    }
})


ServerCommon.CreateWebSocketServer(config.centerServer.forserver.host, config.centerServer.forserver.port, {
    OnRequest(conn:ServerCommon.IWebSocketConn, data:string){
        ServerManager.onReceiveMessage(conn, data)
    },

    OnClose(conn:ServerCommon.IWebSocketConn, reason:number, desc:string){
        ServerManager.onClose(conn, reason, desc);
    },

    OnError(conn:ServerCommon.IWebSocketConn, error:string){
        ServerManager.OnError(conn, error);
    }
})

export class CenterServer implements ServerInteface.ICenterServer{
    
    registerAgent(host:string, port:number, zone:number){
        AgentManager.registerAgent(host, port, zone);
    }
}

var centerserverInstance = new CenterServer()
ServerCommon.CreateDServer(config.centerServer.host, config.centerServer.port, ServerCommon.convert(centerserverInstance) );

process.on('uncaughtException', (error)=>{
    console.log("uncaughtException:" + error)
    var stack = new Error().stack
    console.log( stack )
})