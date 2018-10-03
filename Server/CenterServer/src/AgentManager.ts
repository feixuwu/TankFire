/// <reference path="../typings/index.d.ts" />
/// <reference path="../../Common/common.d.ts" />
/// <reference path="../../Common/routerinterface.d.ts" />

import * as fs from 'fs'
import {QueueClient} from './QueueClient'
import {ServerManager} from './ServerManager'
require("../../Common/common.js")
require("../../Common/message.js")


export interface AgentInfo{
    host:string;        // local host
    port:number;        // port
    zone:number;        // 区域
}

setInterval(()=>{
    AgentManager.checkAlive();
}, 2000)

export class AgentManager{
    static agentList:{[key:string]:AgentInfo} = {}

    static registerAgent(host:string, port:number, zone:number){
        var key = host + "_" + port
        AgentManager.agentList[key] = {host:host, port:port, zone:zone};
        console.log("register agent:" + key)
    }

    static checkAlive(){
        var keys = Object.keys(AgentManager.agentList);
        for(var i = 0; i < keys.length; i++){
            (function(){
            var tmpHost = AgentManager.agentList[keys[i]].host
            var tmpPort = AgentManager.agentList[keys[i]].port
            ServerCommon.GetDnodeClient(tmpHost, tmpPort,(error, client:any)=>{
                if(error != null){
                    var delKey = tmpHost + "_" + tmpPort
                    delete AgentManager.agentList[delKey];
                }
            })
            })();
        }
    }

    static randomCreateServer(zone:number){
        var orgkeys = Object.keys(AgentManager.agentList);
        if(orgkeys.length == 0){
            return;
        }

        var keys:string[] = [];
        for(var i = 0; i < orgkeys.length; i++){
            if(AgentManager.agentList[orgkeys[i]] != null && AgentManager.agentList[orgkeys[i]].zone == zone){
                keys.push(orgkeys[i]);
            }
        }

        if(keys.length == 0){
            return;
        }

        var index = Math.floor(Math.random() * keys.length)
        var tmpAgent = AgentManager.agentList[keys[index]]
        
        ServerCommon.GetDnodeClient(tmpAgent.host, tmpAgent.port, (error, client:ServerInteface.IAgentServer)=>{
            if(error != null){
                return;
            }
            client.createNewServer();
        })
    }
}