/// <reference path="../typings/index.d.ts" />
/// <reference path="../../Common/common.d.ts" />
/// <reference path="../../Common/routerinterface.d.ts" />

import * as fs from 'fs'
import {exec} from 'child_process'

require("../../Common/common.js")
require("../../Common/message.js")
//var exec = require('child_process').exec;

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
    port:number;
    zone:number;
    samplehost:string;
    sampleport:number;
}

export interface Config{
    centerServer:{
        forclient:ServerConfig;
        forserver:ServerConfig;
        host:string;
        port:number;
        gameconfig:GameConfig;
    },
    agentServer:AgentConfig
}

var config:Config = JSON.parse(fs.readFileSync("../Config/config.json", "utf8") )


export class AgentServer implements ServerInteface.IAgentServer{
    
    createNewServer(){
        exec(config.agentServer.cmd, (error, stdout, stderr)=>{
            
        })
    }
}

var agentInstance = new AgentServer();
ServerCommon.CreateDServer(config.agentServer.host, config.agentServer.port, ServerCommon.convert(agentInstance) )

setInterval(()=>{
    ServerCommon.GetDnodeClient(config.centerServer.host, config.centerServer.port, (error, center:ServerInteface.ICenterServer)=>{
        if(error != null){
            console.log(error)
            return;
        }

        center.registerAgent(config.agentServer.host, config.agentServer.port, config.agentServer.zone)
    })
},2000)


if(config.agentServer.samplehost != null && config.agentServer.samplehost.length > 0){
    ServerCommon.CreateWebSocketServer(config.agentServer.samplehost, config.agentServer.sampleport, {
        OnRequest(conn:ServerCommon.IWebSocketConn, data:string){
        },
    
        OnClose(conn:ServerCommon.IWebSocketConn, reason:number, desc:string){
        },
    
        OnError(conn:ServerCommon.IWebSocketConn, error:string){
        }
    })
}


process.on('uncaughtException', (error)=>{
    console.log("uncaughtException:" + error)
    var stack = new Error().stack
    console.log( stack )
})

/*const ws = new WebSocket('ws://192.168.1.107:8889');

ws.on('open', function open() {
  ws.send('something');
});

ws.on('message', function incoming(data) {
  console.log(data);
});*/