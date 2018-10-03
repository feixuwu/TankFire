"use strict";
/// <reference path="../typings/index.d.ts" />
/// <reference path="../../Common/common.d.ts" />
/// <reference path="../../Common/routerinterface.d.ts" />
Object.defineProperty(exports, "__esModule", { value: true });
require("../../Common/common.js");
require("../../Common/message.js");
setInterval(function () {
    AgentManager.checkAlive();
}, 2000);
var AgentManager = /** @class */ (function () {
    function AgentManager() {
    }
    AgentManager.registerAgent = function (host, port, zone) {
        var key = host + "_" + port;
        AgentManager.agentList[key] = { host: host, port: port, zone: zone };
        console.log("register agent:" + key)
    };
    AgentManager.checkAlive = function () {
        var keys = Object.keys(AgentManager.agentList);
        for (var i = 0; i < keys.length; i++) {
            (function () {
                var tmpHost = AgentManager.agentList[keys[i]].host;
                var tmpPort = AgentManager.agentList[keys[i]].port;
                ServerCommon.GetDnodeClient(tmpHost, tmpPort, function (error, client) {
                    if (error != null) {
                        var delKey = tmpHost + "_" + tmpPort;
                        delete AgentManager.agentList[delKey];
                    }
                });
            })();
        }
    };
    AgentManager.randomCreateServer = function (zone) {
        var orgkeys = Object.keys(AgentManager.agentList);
        if (orgkeys.length == 0) {
            return;
        }
        var keys = [];
        for (var i = 0; i < orgkeys.length; i++) {
            if (AgentManager.agentList[orgkeys[i]] != null && AgentManager.agentList[orgkeys[i]].zone == zone) {
                keys.push(orgkeys[i]);
            }
        }
        if (keys.length == 0) {
            return;
        }
        var index = Math.floor(Math.random() * keys.length);
        var tmpAgent = AgentManager.agentList[keys[index]];
        ServerCommon.GetDnodeClient(tmpAgent.host, tmpAgent.port, function (error, client) {
            if (error != null) {
                return;
            }
            client.createNewServer();
        });
    };
    AgentManager.agentList = {};
    return AgentManager;
}());
exports.AgentManager = AgentManager;
//# sourceMappingURL=AgentManager.js.map