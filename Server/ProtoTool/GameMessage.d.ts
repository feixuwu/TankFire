declare namespace GameMessage{
	enum command {
		enum=1,
		CMD_LOGIN=1,
		CMD_REGISTER=2,
		CMD_GAMELIST=3,
		CMD_SERVERLIST=4,
		CMD_CREATE_ROOM=5,
		CMD_JOIN_ROOM=6,
		CMD_GAME_REAY=7,
		CMD_LEAVE_ROOM=8,
		CMD_GAME_START=9,
		CMD_GAME_SENDSCENE=10,
		CMD_GAME_MESSAGE=11,
		CMD_NOTIFY_CURROOM=12,
	}
	enum enGameMode {
		enum=1,
		enComsumeMode_VIP=0,
		enComsumeMode_Card=1,
	}
	export interface CS_CMD_LOGIN_body{
		account:string;
		password:string;
	}
	export interface CS_CMD_LOGIN{
		cmd:number;
		body:CS_CMD_LOGIN_body;
	}
	export interface AccountBaseInfo{
		account:string;
		name:string;
		id:string;
		icon:string;
	}
	export interface SC_CMD_LOGIN_body{
		result:boolean;
		data:AccountBaseInfo;
		errmsg:string;
	}
	export interface SC_CMD_LOGIN{
		cmd:number;
		body:SC_CMD_LOGIN_body;
	}
	export interface CS_CMD_REGISTER_body{
		account:string;
		password:string;
	}
	export interface CS_CMD_REGISTER{
		cmd:number;
		body:CS_CMD_REGISTER_body;
	}
	export interface SC_CMD_REGISTER_body{
		result:boolean;
	}
	export interface SC_CMD_REGISTER{
		cmd:number;
		body:SC_CMD_REGISTER_body;
	}
	export interface GameDefineInfo{
		gameid:string;
		name:string;
	}
	export interface SC_CMD_GAMELIST_body{
		gamelist:GameDefineInfo[];
	}
	export interface SC_CMD_GAMELIST{
		cmd:number;
		body:SC_CMD_GAMELIST_body;
	}
	export interface ServerInfo{
		id:string;
		host:string;
		port:number;
		gamelist:GameDefineInfo[];
	}
	export interface SC_CMD_SERVERLIST_body{
		serverlist:ServerInfo[];
	}
	export interface SC_CMD_SERVERLIST{
		cmd:number;
		body:SC_CMD_SERVERLIST_body;
	}
	export interface CS_CMD_CREATE_ROOM_body{
		gameid:string;
		mode:number;
		gamecount:number;
		playercount:number;
		privaterule:string;
	}
	export interface CS_CMD_CREATE_ROOM{
		cmd:number;
		body:CS_CMD_CREATE_ROOM_body;
	}
	export interface RoomMember{
		name:string;
		id:string;
		ip:string;
		chair:number;
	}
	export interface RoomDetail{
		memberlist:RoomMember[];
		ownerid:string;
		gameid:string;
		roomid:string;
		playercount:number;
		gamecount:number;
		privaterule:string;
		isstarted:boolean;
	}
	export interface SC_CMD_CREATE_ROOM_body{
		result:boolean;
		roominfo:RoomDetail;
		error:string;
	}
	export interface SC_CMD_CREATE_ROOM{
		cmd:number;
		body:SC_CMD_CREATE_ROOM_body;
	}
	export interface CS_CMD_JOIN_ROOM_body{
		roomid:string;
	}
	export interface CS_CMD_JOIN_ROOM{
		cmd:number;
		body:CS_CMD_JOIN_ROOM_body;
	}
	export interface SC_CMD_JOIN_ROOM_body{
		result:boolean;
		roominfo:RoomDetail;
		error:string;
	}
	export interface SC_CMD_JOIN_ROOM{
		cmd:number;
		body:SC_CMD_JOIN_ROOM_body;
	}
	export interface CS_CMD_LEAVE_ROOM{
		cmd:number;
	}
	export interface SC_CMD_LEAVE_ROOM_body{
		result:boolean;
		userid:string;
		error:string;
	}
	export interface SC_CMD_LEAVE_ROOM{
		cmd:number;
		body:SC_CMD_LEAVE_ROOM_body;
	}
	export interface CS_CMD_GAME_REAY{
		cmd:number;
	}
	export interface SC_CMD_GAME_REAY_body{
		result:boolean;
		userid:string;
		error:string;
	}
	export interface SC_CMD_GAME_REAY{
		cmd:number;
		body:SC_CMD_GAME_REAY_body;
	}
	export interface SC_CMD_GAME_START_body{
		privatedata:string;
	}
	export interface SC_CMD_GAME_START{
		cmd:number;
		body:SC_CMD_GAME_START_body;
	}
	export interface SC_CMD_GAME_SENDSCENE_body{
		privatedata:string;
	}
	export interface SC_CMD_GAME_SENDSCENE{
		cmd:number;
		body:SC_CMD_GAME_SENDSCENE_body;
	}
	export interface CS_CMD_GAME_MESSAGE_body{
		privatedata:string;
	}
	export interface CS_CMD_GAME_MESSAGE{
		cmd:number;
		subcmd:number;
		body:CS_CMD_GAME_MESSAGE_body;
	}
	export interface SC_CMD_GAME_MESSAGE_body{
		privatedata:string;
	}
	export interface SC_CMD_GAME_MESSAGE{
		cmd:number;
		subcmd:number;
		body:SC_CMD_GAME_MESSAGE_body;
	}
	export interface SC_CMD_NOTIFY_CURROOM_body{
		existroom:boolean;
		roomlist:RoomDetail[];
	}
	export interface SC_CMD_NOTIFY_CURROOM{
		cmd:number;
		body:SC_CMD_NOTIFY_CURROOM_body;
	}

}