declare namespace AgentMessage{
	enum command {
		enum=1,
		QUERY_ALL_PLAYER=1,
		SET_AGENT=2,
		AGENT_LOGIN=4,
		AGENT_SEARCH_PLAYER=5,
		AGENT_GIVE_ROOMCARD=6,
		AGENT_QUERY_GIVELOG=7,
		AGENT_QUERY_CONSUMELOG=8,
		AGENT_QUERY_ALLCHILDAGENT=9,
		AGENT_CHG_PASSWD=10,
		AGENT_LOGOUT=11,
		CMD_REQUEST_ADMINHOMEPAGE=12,
		CMD_REALTIME_INFO=13,
		CMD_QUERY_AGENTT_CHILD=14,
		CMD_QUERY_PLAYERINFO=15,
		CMD_QUERY_ADMIN_LIST=16,
		CMD_ADD_ADMIN=17,
		CMD_ADMIN_EDIT=18,
	}
	enum enReqType {
		enum=1,
		enReqType_YEAR=1,
		enReqType_Cur_Month=2,
		enReqType_Last_Month=3,
		enReqType_Today=4,
		enReqType_YesterDay=5,
		enReqType_Date=6,
	}
	enum enDataType {
		enum=1,
		enDataType_newPlayer=1,
		enDataType_RoomCardConsume=2,
		enDataType_InGamePlayer=3,
		enDataType_GiveRoomCard=4,
	}
	enum enPermission {
		enum=1,
		enPermission_Super=-1,
		enPermission_Admin=0,
		enPermission_Other=1,
	}
	export interface CS_CMD_QUERY_ADMIN_LIST{
		cmd:number;
	}
	export interface AdminInfo{
		id:string;
		iLv:number;
		signUpTime:number;
		signUpIp:number;
	}
	export interface SC_CMD_QUERY_ADMIN_LIST_body{
		adminList:AdminInfo[];
	}
	export interface SC_CMD_QUERY_ADMIN_LIST{
		cmd:number;
		body:SC_CMD_QUERY_ADMIN_LIST_body;
	}
	export interface CS_CMD_ADD_ADMIN_body{
		iLv:number;
		id:string;
		key:string;
	}
	export interface CS_CMD_ADD_ADMIN{
		cmd:number;
		body:CS_CMD_ADD_ADMIN_body;
	}
	export interface SC_CMD_ADD_ADMIN_body{
		result:boolean;
		errmsg:string;
	}
	export interface SC_CMD_ADD_ADMIN{
		cmd:number;
		body:SC_CMD_ADD_ADMIN_body;
	}
	export interface CS_CMD_ADMIN_EDIT_body{
		iLv:number;
		key:string;
		id:string;
	}
	export interface CS_CMD_ADMIN_EDIT{
		cmd:number;
		body:CS_CMD_ADMIN_EDIT_body;
	}
	export interface SC_CMD_ADMIN_EDIT_body{
		result:boolean;
		errmsg:string;
	}
	export interface SC_CMD_ADMIN_EDIT{
		cmd:number;
		body:SC_CMD_ADMIN_EDIT_body;
	}
	export interface CS_CMD_QUERY_PLAYERINFO_body{
		userid:number;
	}
	export interface CS_CMD_QUERY_PLAYERINFO{
		cmd:number;
		body:CS_CMD_QUERY_PLAYERINFO_body;
	}
	export interface SC_CMD_QUERY_PLAYERINFO_body{
		playerinfo:PlayerInfo;
	}
	export interface SC_CMD_QUERY_PLAYERINFO{
		cmd:number;
		body:SC_CMD_QUERY_PLAYERINFO_body;
	}
	export interface CS_CMD_QUERY_AGENTT_CHILD_body{
		userId:number;
	}
	export interface CS_CMD_QUERY_AGENTT_CHILD{
		cmd:number;
		body:CS_CMD_QUERY_AGENTT_CHILD_body;
	}
	export interface AgentInfo{
		agentId:string;
		userId:number;
		iLv:number;
		roomcardCnt:number;
	}
	export interface SC_CMD_QUERY_AGENTT_CHILD_body{
		agentList:AgentInfo[];
	}
	export interface SC_CMD_QUERY_AGENTT_CHILD{
		cmd:number;
		body:SC_CMD_QUERY_AGENTT_CHILD_body;
	}
	export interface CS_CMD_REALTIME_INFO_body{
		reqType:number;
		begin:string;
		end:string;
	}
	export interface CS_CMD_REALTIME_INFO{
		cmd:number;
		body:CS_CMD_REALTIME_INFO_body;
	}
	export interface DataNode{
		dataType:number;
		X:number;
		Y:number;
	}
	export interface SC_CMD_REALTIME_INFO_body{
		reqType:number;
		dataList:DataNode[];
	}
	export interface SC_CMD_REALTIME_INFO{
		cmd:number;
		body:SC_CMD_REALTIME_INFO_body;
	}
	export interface SC_CMD_REQUEST_ADMINHOMEPAGE_body{
		agentCount:number;
		totalGiveRoomCard:number;
		todayGive:number;
		totalConsume:number;
		todayConsume:number;
		playerRoomCard:number;
		playerCount:number;
		newPlayer:number;
		todayLogin:number;
		stopagentCnt:number;
	}
	export interface SC_CMD_REQUEST_ADMINHOMEPAGE{
		cmd:number;
		body:SC_CMD_REQUEST_ADMINHOMEPAGE_body;
	}
	export interface CS_AGENT_CHG_PASSWD_body{
		curPassWd:string;
		newPassWd:string;
	}
	export interface CS_AGENT_CHG_PASSWD{
		cmd:number;
		body:CS_AGENT_CHG_PASSWD_body;
	}
	export interface SC_AGENT_CHG_PASSWD_body{
		result:boolean;
		errmsg:string;
	}
	export interface SC_AGENT_CHG_PASSWD{
		cmd:number;
		body:SC_AGENT_CHG_PASSWD_body;
	}
	export interface CS_AGENT_LOGOUT{
		cmd:number;
	}
	export interface SC_AGENT_LOGOUT{
		cmd:number;
	}
	export interface PlayerInfo{
		UserId:number;
		Nickname:string;
		CardNum:number;
		GoldNum:number;
		SignUpTimes:number;
		GameTime:number;
		OnLineTime:number;
		SignUpTime:number;
		SignUpIP:string;
		RegisterTime:number;
		RegisterIp:string;
	}
	export interface CS_AGENT_QUERY_ALLCHILDAGENT_body{
		reqBegin:number;
		reqCount:number;
	}
	export interface CS_AGENT_QUERY_ALLCHILDAGENT{
		cmd:number;
		body:CS_AGENT_QUERY_ALLCHILDAGENT_body;
	}
	export interface SC_AGENT_QUERY_ALLCHILDAGENT_body{
		playerList:PlayerInfo[];
	}
	export interface SC_AGENT_QUERY_ALLCHILDAGENT{
		cmd:number;
		body:SC_AGENT_QUERY_ALLCHILDAGENT_body;
	}
	export interface CS_QUERY_ALL_PLAYER_body{
		reqPage:number;
	}
	export interface CS_QUERY_ALL_PLAYER{
		cmd:number;
		body:CS_QUERY_ALL_PLAYER_body;
	}
	export interface SC_QUERY_ALL_PLAYER_body{
		reqPage:number;
		playerList:PlayerInfo[];
	}
	export interface SC_QUERY_ALL_PLAYER{
		cmd:number;
		body:SC_QUERY_ALL_PLAYER_body;
	}
	export interface CS_SET_AGENT_body{
		pAgentId:string;
		userId:number;
		prefix:string;
		key:string;
	}
	export interface CS_SET_AGENT{
		cmd:number;
		body:CS_SET_AGENT_body;
	}
	export interface SC_SET_AGENT_body{
		result:boolean;
		errmsg:string;
	}
	export interface SC_SET_AGENT{
		cmd:number;
		body:SC_SET_AGENT_body;
	}
	export interface CS_AGENT_LOGIN_body{
		id:string;
		passwd:string;
	}
	export interface CS_AGENT_LOGIN{
		cmd:number;
		body:CS_AGENT_LOGIN_body;
	}
	export interface SC_AGENT_LOGIN_body{
		result:boolean;
		errmsg:string;
		permission:number;
		AgentId:string;
		RemainRoomCard:number;
		userId:number;
	}
	export interface SC_AGENT_LOGIN{
		cmd:number;
		body:SC_AGENT_LOGIN_body;
	}
	export interface CS_AGENT_SEARCH_PLAYER_body{
		UserId:number;
	}
	export interface CS_AGENT_SEARCH_PLAYER{
		cmd:number;
		body:CS_AGENT_SEARCH_PLAYER_body;
	}
	export interface SC_AGENT_SEARCH_PLAYER_body{
		result:boolean;
		errmsg:string;
		player:PlayerInfo;
		selfRemaindRoomCard:number;
		selfDayGiveRoomCard:number;
	}
	export interface SC_AGENT_SEARCH_PLAYER{
		cmd:number;
		body:SC_AGENT_SEARCH_PLAYER_body;
	}
	export interface CS_AGENT_GIVE_ROOMCARD_body{
		userId:number;
		value:number;
		reason:string;
	}
	export interface CS_AGENT_GIVE_ROOMCARD{
		cmd:number;
		body:CS_AGENT_GIVE_ROOMCARD_body;
	}
	export interface SC_AGENT_GIVE_ROOMCARD_body{
		result:boolean;
		errmsg:string;
	}
	export interface SC_AGENT_GIVE_ROOMCARD{
		cmd:number;
		body:SC_AGENT_GIVE_ROOMCARD_body;
	}
	export interface CS_AGENT_QUERY_GIVELOG{
		cmd:number;
	}
	export interface GiveUnit{
		time:number;
		value:number;
		giveId:number;
		BeforGiveValue:number;
	}
	export interface SC_AGENT_QUERY_GIVELOG_body{
		giveList:GiveUnit[];
	}
	export interface SC_AGENT_QUERY_GIVELOG{
		cmd:number;
		body:SC_AGENT_QUERY_GIVELOG_body;
	}
	export interface CS_AGENT_QUERY_CONSUMELOG{
		cmd:number;
	}
	export interface playerRes{
		name:string;
		score:number;
		playerId:string;
	}
	export interface GameDetail{
		bWin:boolean;
		playerList:playerRes[];
	}
	export interface ConsumeLog{
		time:string;
		value:number;
		roomId:number;
		detail:GameDetail;
	}
	export interface SC_AGENT_QUERY_CONSUMELOG_body{
		cosumeList:ConsumeLog[];
	}
	export interface SC_AGENT_QUERY_CONSUMELOG{
		cmd:number;
		body:SC_AGENT_QUERY_CONSUMELOG_body;
	}

}