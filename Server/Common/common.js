//var  ProtoBuf = require('protobufjs')
var fs = require('fs')
var uuidgen = require('node-uuid');
var dnode = require('dnode');
const WebSocket = require('ws');

var fs = require('fs');

global.WebSocket = WebSocket;
global.ServerCommon = {};

var g_dnoceClient = {};
global.ServerCommon.GetDnodeClient = function(host, port, cb)
{
    var searchKey = host + '_' + port;
    if(g_dnoceClient[searchKey] != undefined)
    {
        if(cb != null)
        {
            cb(null, g_dnoceClient[searchKey]);
            cb = null;
            return;
        }
    }

    var tmpd = dnode.connect(host, port);
    tmpd.on('remote', function (remote) 
    {
        g_dnoceClient[searchKey] = remote;
        if(cb != null)cb(null, remote);
        cb = null;
    });

    tmpd.on('error', function(error)
    {
        g_dnoceClient[searchKey] = null;
        if(cb != null)cb(error, null);
        cb = null;
        console.log("GetDnodeClient|error|" +host + "|" + port + "|" + error);
    });
}

global.ServerCommon.CreateDServer = function(host, port, fundic)
{
    var dserver = dnode(fundic);
    var server = dserver.listen(host, port)
    server.on('remote', function(remote, d)
    {
        d.on('error', function(err)
        {
            console.log('dserver|remote|error|' + host + "|" + port + "|"  + err);
            console.log(err.stack);
        } );
    });

    server.on('error', function(err)
    {
        console.log('dserver|remote|error|' + host + "|" + port + "|"  + err);
    })

    dserver.on('error', function(err)
    {
        console.log('dserver|error|' + host + "|" + port + "|" +  err);
    });
}

global.ServerCommon.CreateWebSocketServer = function(host, port, cb)
{
    var server = new WebSocket.Server({ port: port, host:host} );
    server.on('connection', function connection(client) {
    client.on('message', function incoming(message) {
         cb.OnRequest(client, message);
    });

    client.on('close', function (errno, message) {
        cb.OnClose(client, errno, message);
    });
    
    client.on('error', function(err){
        cb.OnError(client, err);
    } )
});

}

global.ServerCommon.UUIDGenerate= ()=>
{
    return uuidgen.v4();
}

global.ServerCommon.convert=(v)=>
{
    var ret = v;
    
    for(var k in v.__proto__){
        if(typeof(v[k]) == 'function'){
            (()=>{
                var func = v[k];
                ret[k] = function(){
                    try
                    {
                        return func.apply(v, arguments)
                    }
                    catch(e){
                        console.log("error:" + e)
                    }
                }
            })();
        }
    }

    return ret;
}

/*var test = new builer.CSMessage();
test.iCmd = builer.GAMECMD.CMD_PING;

var buf = test.encode();

var test2 = new builer.CSMessage();
var xx = builer.CSMessage.decode(buf);

console.log("***")*/