"use strict";
/// <reference path="../typings/index.d.ts" />
/// <reference path="../../Common/common.d.ts" />
/// <reference path="../../Common/routerinterface.d.ts" />
/// <reference path="../../Common/MessageProto.d.ts" />
Object.defineProperty(exports, "__esModule", { value: true });
var fs = require("fs");
var QueueClient_1 = require("./QueueClient");
var ServerManager_1 = require("./ServerManager");
var AgentManager_1 = require("./AgentManager");
require("../../Common/common.js");
require("../../Common/message.js");
var config = JSON.parse(fs.readFileSync("../Config/config.json", "utf8"));
ServerCommon.CreateWebSocketServer(config.centerServer.forclient.host, config.centerServer.forclient.port, {
    OnRequest: function (conn, data) {
        QueueClient_1.QueueClient.onReceiveMessage(conn, data);
    },
    OnClose: function (conn, reason, desc) {
        QueueClient_1.QueueClient.onClose(conn, reason, desc);
    },
    OnError: function (conn, error) {
        QueueClient_1.QueueClient.OnError(conn, error);
    }
});
ServerCommon.CreateWebSocketServer(config.centerServer.forserver.host, config.centerServer.forserver.port, {
    OnRequest: function (conn, data) {
        ServerManager_1.ServerManager.onReceiveMessage(conn, data);
    },
    OnClose: function (conn, reason, desc) {
        ServerManager_1.ServerManager.onClose(conn, reason, desc);
    },
    OnError: function (conn, error) {
        ServerManager_1.ServerManager.OnError(conn, error);
    }
});
var CenterServer = /** @class */ (function () {
    function CenterServer() {
    }
    CenterServer.prototype.registerAgent = function (host, port, zone) {
        AgentManager_1.AgentManager.registerAgent(host, port, zone);
    };
    return CenterServer;
}());
exports.CenterServer = CenterServer;
var centerserverInstance = new CenterServer();
ServerCommon.CreateDServer(config.centerServer.host, config.centerServer.port, ServerCommon.convert(centerserverInstance));
process.on('uncaughtException', function (error) {
    console.log("uncaughtException:" + error);
    var stack = new Error().stack;
    console.log(stack);
});
//# sourceMappingURL=CenterServer.js.map