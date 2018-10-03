"use strict";
/// <reference path="../typings/index.d.ts" />
/// <reference path="../../Common/common.d.ts" />
/// <reference path="../../Common/routerinterface.d.ts" />
Object.defineProperty(exports, "__esModule", { value: true });
var fs = require("fs");
var child_process_1 = require("child_process");
require("../../Common/common.js");
require("../../Common/message.js");
var config = JSON.parse(fs.readFileSync("../Config/config.json", "utf8"));
var AgentServer = /** @class */ (function () {
    function AgentServer() {
    }
    AgentServer.prototype.createNewServer = function () {
        console.log("ready create server")
        child_process_1.exec(config.agentServer.cmd, function (error, stdout, stderr) {
            if(error != null){
                console.log(error + stdout)
            }
        });
    };
    return AgentServer;
}());
exports.AgentServer = AgentServer;
var agentInstance = new AgentServer();
ServerCommon.CreateDServer(config.agentServer.host, config.agentServer.port, ServerCommon.convert(agentInstance));
setInterval(function () {
    ServerCommon.GetDnodeClient(config.centerServer.host, config.centerServer.port, function (error, center) {
        if (error != null) {
            console.log(error);
            return;
        }
        console.log("readt register agent")
        center.registerAgent(config.agentServer.host, config.agentServer.port, config.agentServer.zone);
    });
}, 2000);
if (config.agentServer.samplehost != null && config.agentServer.samplehost.length > 0) {
    ServerCommon.CreateWebSocketServer(config.agentServer.samplehost, config.agentServer.sampleport, {
        OnRequest: function (conn, data) {
        },
        OnClose: function (conn, reason, desc) {
        },
        OnError: function (conn, error) {
        }
    });
}
process.on('uncaughtException', function (error) {
    console.log("uncaughtException:" + error);
    var stack = new Error().stack;
    console.log(stack);
});
/*const ws = new WebSocket('ws://192.168.1.107:8889');

ws.on('open', function open() {
  ws.send('something');
});

ws.on('message', function incoming(data) {
  console.log(data);
});*/ 
//# sourceMappingURL=AgentServer.js.map