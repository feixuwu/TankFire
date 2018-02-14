declare namespace MessageProto{
	enum command {
		enum=1,
		CMD_CLIENT_REQUEST_QUEUE=1,
		CMD_CLIENT_JOIN_GAME=2,
		CMD_CLIENT_EMOTION=3,
		CMD_CLIENT_CANCEL_QUEUE=16,
		CMD_CLIENT_QUERYZONE=17,
		CMD_CLIENT_QUERYACCOUNT=18,
		CMD_GS_FETCH_USERTOKEN=4,
		CMD_GS_ADD_USER=5,
		CMD_GS_QUERYACCOUNT=101,
		CMD_GS_UPDATEACCOUNT=102,
		CMD_GS_CLOSE=103,
	}
	enum enResult {
		enum=1,
		enResult_OK=0,
		enResult_Fail=1,
	}
	export interface CS_CMD_GS_CLOSE{
		cmd:number;
	}
	export interface CS_CMD_CLIENT_QUERYACCOUNT{
		cmd:number;
		account:string;
		name:string;
	}
	export interface AccountData{
		account:string;
		name:string;
		cup:number;
		segment:number;
		star:number;
	}
	export interface CS_CMD_GS_UPDATEACCOUNT{
		cmd:number;
		accountData:AccountData;
	}
	export interface CS_CMD_GS_QUERYACCOUNT{
		cmd:number;
		accout:string;
	}
	export interface SC_CMD_GS_QUERYACCOUNT{
		cmd:number;
		result:number;
		accountData:AccountData;
	}
	export interface SC_CMD_CLIENT_QUERYACCOUNT{
		cmd:number;
		accountData:AccountData;
	}
	export interface ServerZone{
		Id:number;
		name:string;
		sampleIp:string;
		sampleport:number;
	}
	export interface SC_CMD_CLIENT_QUERYZONE{
		cmd:number;
		zoneList:ServerZone[];
	}
	export interface CS_CMD_CLIENT_QUERYZONE{
		cmd:number;
	}
	export interface CS_CMD_CLIENT_CANCEL_QUEUE{
		cmd:number;
	}
	export interface SC_CMD_CLIENT_CANCEL_QUEUE{
		cmd:number;
		result:boolean;
	}
	export interface UserInfo{
		account:string;
		name:string;
		headurl:string;
	}
	export interface UserTokenInfo{
		account:string;
		name:string;
		headurl:string;
		token:string;
	}
	export interface SC_CMD_GS_ADD_USER{
		cmd:number;
		newUser:UserTokenInfo;
	}
	export interface CS_CMD_GS_FETCH_USERTOKEN{
		cmd:number;
		serverKey:string;
		host:string;
		port:number;
		zone:number;
	}
	export interface SC_CMD_GS_FETCH_USERTOKEN{
		cmd:number;
		result:number;
		userList:UserTokenInfo[];
	}
	export interface CS_CMD_CLIENT_REQUEST_QUEUE{
		cmd:number;
		userInfo:UserInfo;
		zoneId:number;
	}
	export interface SC_CMD_CLIENT_REQUEST_QUEUE{
		cmd:number;
		result:number;
		token:string;
		zoneId:number;
	}
	export interface SC_CMD_CLIENT_JOIN_GAME{
		cmd:number;
		host:string;
		port:number;
		serverkey:string;
	}
	export interface CS_CMD_CLIENT_EMOTION{
		cmd:number;
		serverKey:string;
		emotion:number;
	}
	export interface SC_CMD_CLIENT_EMOTION{
		cmd:number;
		account:string;
		emotion:number;
	}

}