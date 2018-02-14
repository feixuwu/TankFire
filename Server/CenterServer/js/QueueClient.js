"use strict";
/// <reference path="../typings/index.d.ts" />
/// <reference path="../../Common/common.d.ts" />
/// <reference path="../../Common/routerinterface.d.ts" />
/// <reference path="../../Common/MessageProto.d.ts" />
Object.defineProperty(exports, "__esModule", { value: true });
var ServerManager_1 = require("./ServerManager");
var fs = require("fs");
var redis = require("redis");
var buffer_1 = require("buffer");
var config = JSON.parse(fs.readFileSync("../Config/config.json", "utf8"));
var redisconn = redis.createClient(config.centerServer.redisport, config.centerServer.redishost);
redisconn.on('error', function (err) {
    console.log("Redis Error:" + err);
});
var QueueClient = /** @class */ (function () {
    function QueueClient() {
    }
    QueueClient.getRedisConn = function () {
        return redisconn;
    };
    QueueClient.onReceiveMessage = function (conn, data) {
        try {
            var dataObj = JSON.parse(data);
            console.log("~~~~csMsg" + data);
            QueueClient.processMessage(conn, dataObj);
        }
        catch (e) {
            console.log("invalid message:" + data);
        }
    };
    QueueClient.processMessage = function (conn, message) {
        switch (message.cmd) {
            case MessageProto.command.CMD_CLIENT_REQUEST_QUEUE:
                QueueClient.processRequestQueue(conn, message);
                break;
            case MessageProto.command.CMD_CLIENT_EMOTION:
                QueueClient.processEmotion(conn, message);
                break;
            case MessageProto.command.CMD_CLIENT_CANCEL_QUEUE:
                QueueClient.processCancelRequestQueue(conn, message);
                break;
            case MessageProto.command.CMD_CLIENT_QUERYZONE:
                QueueClient.processQueryZoneList(conn, message);
                break;
            case MessageProto.command.CMD_CLIENT_QUERYACCOUNT:
                QueueClient.processQueryAccount(conn, message);
                break;
        }
    };
    QueueClient.processQueryAccount = function (conn, message) {
        if (message.account == null) {
            return;
        }
        var accountKey = new buffer_1.Buffer(message.account).toString("base64");
        redisconn.get(accountKey, function (error, data) {
            if (error != null) {
                console.log("client get account error:" + error);
                return;
            }
            var needFlush = false;
            var accountData = null;
            if (data == null) {
                accountData = {
                    account: message.account,
                    name: message.name,
                    cup: 0,
                    segment: 0,
                    star: 0,
                };
                needFlush = true;
            }
            else {
                var orgData = new buffer_1.Buffer(data, "base64").toString();
                accountData = JSON.parse(orgData);
                needFlush = accountData.name != message.name;
            }
            if (needFlush) {
                var saveData = new buffer_1.Buffer(JSON.stringify(accountData)).toString("base64");
                redisconn.set(accountKey, saveData);
            }
            var scMessage = {
                cmd: MessageProto.command.CMD_CLIENT_QUERYACCOUNT,
                accountData: accountData
            };
            QueueClient.sendSCMessage(conn, scMessage);
        });
    };
    QueueClient.processQueryZoneList = function (conn, message) {
        var scMessage = {
            cmd: MessageProto.command.CMD_CLIENT_QUERYZONE,
            zoneList: config.centerServer.zonelist,
        };
        QueueClient.sendSCMessage(conn, scMessage);
    };
    QueueClient.processCancelRequestQueue = function (conn, message) {
        var key = QueueClient.getKey(conn);
        if (QueueClient.socketMap[key] == null) {
            return;
        }
        var connUser = QueueClient.socketMap[key]._user;
        var scMessage = {
            cmd: MessageProto.command.CMD_CLIENT_CANCEL_QUEUE,
            result: true
        };
        var connUserInfo = conn._user;
        // 已经在游戏中了, 不能取消了，但是可以返回客户端成功，客户端不会自动进入游戏
        var ownGameInfo = ServerManager_1.ServerManager.getOwnGame(connUserInfo.account);
        if (ownGameInfo != null) {
            scMessage.result = true;
            QueueClient.sendSCMessage(conn, scMessage);
            return;
        }
        // 在队列了, 可以取消
        var zoneQueueList = QueueClient.clientQueueList[connUser.zone];
        if (zoneQueueList != null) {
            for (var i = 0; i < zoneQueueList.length; i++) {
                if (zoneQueueList[i].accountInfo.strAccount == connUserInfo.account) {
                    zoneQueueList.splice(i, 1);
                    QueueClient.sendSCMessage(conn, scMessage);
                    return;
                }
            }
        }
        // 或者在ReadyPair列表里了, 也是可以取消的
        var zoneReadyPairList = ServerManager_1.ServerManager.readyPairList[connUser.zone];
        for (var i = 0; i < zoneReadyPairList.length; i++) {
            for (var j = 0; j < zoneReadyPairList[i].userList.length; j++) {
                if (zoneReadyPairList[i].userList[j].strAccount == connUserInfo.account) {
                    zoneReadyPairList[i].userList.splice(j, 1);
                    QueueClient.sendSCMessage(conn, scMessage);
                    return;
                }
            }
        }
        // 哪里都不在，当然可以取消
        QueueClient.sendSCMessage(conn, scMessage);
    };
    QueueClient.processRequestQueue = function (conn, message) {
        if (message.zoneId == null) {
            return;
        }
        var isZoneValid = false;
        for (var i = 0; i < config.centerServer.zonelist.length; i++) {
            if (config.centerServer.zonelist[i].Id == message.zoneId) {
                isZoneValid = true;
                break;
            }
        }
        if (!isZoneValid) {
            return;
        }
        var key = QueueClient.getKey(conn);
        if (QueueClient.socketMap[key] == null) {
            QueueClient.socketMap[key] = conn;
            var connUserInfo = {
                key: key,
                account: message.userInfo.account,
                serverKey: "",
                zone: message.zoneId,
            };
            conn._user = connUserInfo;
        }
        var scMessage = {
            cmd: MessageProto.command.CMD_CLIENT_REQUEST_QUEUE,
            result: MessageProto.enResult.enResult_OK,
            token: ServerCommon.UUIDGenerate(),
            zoneId: message.zoneId,
        };
        // 是否已经在游戏中?
        var ownGameInfo = ServerManager_1.ServerManager.getOwnGame(message.userInfo.account);
        if (ownGameInfo != null) {
            for (var i = 0; i < ownGameInfo.userList.length; i++) {
                if (ownGameInfo.userList[i].strAccount == message.userInfo.account) {
                    ownGameInfo.userList[i].connKey = key;
                    scMessage.token = ownGameInfo.userList[i].strToken;
                    break;
                }
            }
            // 通知客户端成功
            QueueClient.sendSCMessage(conn, scMessage);
            // 通知客户端加入游戏
            var scClientMsg = {
                cmd: MessageProto.command.CMD_CLIENT_JOIN_GAME,
                host: ownGameInfo.serverInfo.host,
                port: ownGameInfo.serverInfo.port,
                serverkey: ownGameInfo.serverInfo.serverKey,
            };
            QueueClient.sendSCMessage(conn, scClientMsg);
            return;
        }
        // 也可能已经在队列了
        var zoneQueueList = QueueClient.clientQueueList[message.zoneId];
        if (zoneQueueList != null) {
            for (var i = 0; i < zoneQueueList.length; i++) {
                if (zoneQueueList[i].accountInfo.strAccount == message.userInfo.account) {
                    zoneQueueList[i].accountInfo.connKey = key;
                    scMessage.token = ownGameInfo.userList[i].strToken;
                    QueueClient.sendSCMessage(conn, scMessage);
                    return;
                }
            }
        }
        // 或者在ReadyPair列表里了
        var zoneReadyPairList = ServerManager_1.ServerManager.readyPairList[message.zoneId];
        if (zoneReadyPairList != null) {
            for (var i = 0; i < zoneReadyPairList.length; i++) {
                for (var j = 0; j < zoneReadyPairList[i].userList.length; j++) {
                    if (zoneReadyPairList[i].userList[j].strAccount == message.userInfo.account) {
                        zoneReadyPairList[i].userList[j].connKey = key;
                        scMessage.token = zoneReadyPairList[i].userList[j].strToken;
                        QueueClient.sendSCMessage(conn, scMessage);
                    }
                }
            }
        }
        // 没有，填充请求，放入队列
        var newRequest = {
            key: key,
            zone: message.zoneId,
            accountInfo: {
                strAccount: message.userInfo.account,
                strToken: scMessage.token,
                headiconurl: message.userInfo.headurl,
                strName: message.userInfo.name,
                connKey: key,
            }
        };
        if (QueueClient.clientQueueList[message.zoneId] == null) {
            // check if zone valid
            var find = false;
            for (var i = 0; i < config.centerServer.zonelist.length; i++) {
                if (config.centerServer.zonelist[i].Id == message.zoneId) {
                    find = true;
                    break;
                }
            }
            if (!find) {
                return;
            }
            QueueClient.clientQueueList[message.zoneId] = [];
        }
        QueueClient.clientQueueList[message.zoneId].push(newRequest);
        // 通知客户端
        QueueClient.sendSCMessage(conn, scMessage);
    };
    QueueClient.sendSCMessage = function (conn, data) {
        conn.send(JSON.stringify(data), null, function (error) {
            if (error != null) {
                return;
            }
        });
    };
    QueueClient.getClient = function (key) {
        return QueueClient.socketMap[key];
    };
    QueueClient.processEmotion = function (conn, message) {
        //var ownGameInfo = ServerManager.getOwnGame(message.userInfo.account)
        var connUserInfo = conn._user;
        if (connUserInfo == null) {
            return;
        }
        var ownGameInfo = ServerManager_1.ServerManager.getOwnGame(connUserInfo.account);
        if (ownGameInfo == null) {
            return;
        }
        // 广播
        var scMsg = {
            cmd: MessageProto.command.CMD_CLIENT_EMOTION,
            account: connUserInfo.account,
            emotion: message.emotion,
        };
        for (var i = 0; i < ownGameInfo.userList.length; i++) {
            var client = QueueClient.getClient(ownGameInfo.userList[i].connKey);
            QueueClient.sendSCMessage(client, scMsg);
        }
    };
    QueueClient.onClose = function (conn, reason, desc) {
        QueueClient.removeConn(conn);
    };
    QueueClient.OnError = function (conn, error) {
        QueueClient.removeConn(conn);
    };
    QueueClient.removeConn = function (conn) {
        if (conn._user == null) {
            return;
        }
        var key = conn._user.key;
        if (QueueClient.socketMap[key] != null) {
            var conUser = QueueClient.socketMap[key]._user;
            var zone = conUser.zone;
            delete QueueClient.socketMap[key];
            var zoneQueueList = QueueClient.clientQueueList[zone];
            if (zoneQueueList != null) {
                for (var i = 0; i < zoneQueueList.length; i++) {
                    if (key == zoneQueueList[i].key) {
                        zoneQueueList.splice(i, 1);
                        return;
                    }
                }
            }
        }
    };
    QueueClient.getKey = function (conn) {
        var key = conn._socket.remoteAddress + "_" + conn._socket.remotePort;
        return key;
    };
    QueueClient.clientQueueList = {};
    QueueClient.socketMap = {};
    return QueueClient;
}());
exports.QueueClient = QueueClient;
//# sourceMappingURL=QueueClient.js.map