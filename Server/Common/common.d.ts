
declare namespace ServerCommon{


    export interface IWebSocketConn
    {
        _socket:any;
        _user?:any;
        send(data:string, option:any, cb:(Error)=>void): void;
        close();
    }

    export interface IWebsocketCallback
    {
        OnRequest(conn:IWebSocketConn, data:string);
        OnClose(conn:IWebSocketConn, reason:number, desc:string);
        OnError(conn:IWebSocketConn, error:string);
    }

    var GetDnodeClient:(host:String, port:Number, cb:(error, client:any)=>any)=>void;
    var CreateDServer:(host:String, port:Number, rpc:{[key:string]:(...params:any[])=>any})=>void;
    var CreateWebSocketServer:(host:string, port:number, cb:IWebsocketCallback)=>void;
    var UUIDGenerate:()=>string;
    var convert:(v:any)=>{[key:string]:(...params:any[])=>any};
}