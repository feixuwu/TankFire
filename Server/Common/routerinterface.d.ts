declare namespace ServerInteface{

    export interface IConnInfo
    {
        host:string;    // RS的host
        port:number;    // RS的port
        key:string;     // connection key
    }

    export interface GameServer
    {
        host:string;    // RS的host
        port:number;    // RS的port
        serverKey:string;   // Server唯一Key
        _user:any;
        zone:number;
    }

    export interface UserToken{
        strAccount:string;
        strToken:string;
        headiconurl:string;
        strName:string;
        connKey:string;
    }

    export interface GameServerStatus{
        userList:UserToken[];
        serverInfo:GameServer;
    }

    export interface IAgentServer{
        createNewServer();
    }
    
    export interface ICenterServer{
        registerAgent(host:string, port:number, zone:number);
    }
}