using UnityEngine; 
using System; 
namespace AgentProto{
	public enum command {
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
	public enum enReqType {
		enReqType_YEAR=1,
		enReqType_Cur_Month=2,
		enReqType_Last_Month=3,
		enReqType_Today=4,
		enReqType_YesterDay=5,
		enReqType_Date=6,
	}
	public enum enDataType {
		enDataType_newPlayer=1,
		enDataType_RoomCardConsume=2,
		enDataType_InGamePlayer=3,
		enDataType_GiveRoomCard=4,
	}
	public enum enPermission {
		enPermission_Super=-1,
		enPermission_Admin=0,
		enPermission_Other=1,
	}
	[Serializable]
	public class CS_CMD_QUERY_ADMIN_LIST{
		public int cmd;
	}
	[Serializable]
	public class AdminInfo{
		public string id;
		public int iLv;
		public int signUpTime;
		public int signUpIp;
	}
	[Serializable]
	public class SC_CMD_QUERY_ADMIN_LIST_body{
		public AdminInfo[] adminList;
	}
	[Serializable]
	public class SC_CMD_QUERY_ADMIN_LIST{
		public int cmd;
		public SC_CMD_QUERY_ADMIN_LIST_body body;
	}
	[Serializable]
	public class CS_CMD_ADD_ADMIN_body{
		public int iLv;
		public string id;
		public string key;
	}
	[Serializable]
	public class CS_CMD_ADD_ADMIN{
		public int cmd;
		public CS_CMD_ADD_ADMIN_body body;
	}
	[Serializable]
	public class SC_CMD_ADD_ADMIN_body{
		public bool result;
		public string errmsg;
	}
	[Serializable]
	public class SC_CMD_ADD_ADMIN{
		public int cmd;
		public SC_CMD_ADD_ADMIN_body body;
	}
	[Serializable]
	public class CS_CMD_ADMIN_EDIT_body{
		public int iLv;
		public string key;
		public string id;
	}
	[Serializable]
	public class CS_CMD_ADMIN_EDIT{
		public int cmd;
		public CS_CMD_ADMIN_EDIT_body body;
	}
	[Serializable]
	public class SC_CMD_ADMIN_EDIT_body{
		public bool result;
		public string errmsg;
	}
	[Serializable]
	public class SC_CMD_ADMIN_EDIT{
		public int cmd;
		public SC_CMD_ADMIN_EDIT_body body;
	}
	[Serializable]
	public class CS_CMD_QUERY_PLAYERINFO_body{
		public int userid;
	}
	[Serializable]
	public class CS_CMD_QUERY_PLAYERINFO{
		public int cmd;
		public CS_CMD_QUERY_PLAYERINFO_body body;
	}
	[Serializable]
	public class SC_CMD_QUERY_PLAYERINFO_body{
		public PlayerInfo playerinfo;
	}
	[Serializable]
	public class SC_CMD_QUERY_PLAYERINFO{
		public int cmd;
		public SC_CMD_QUERY_PLAYERINFO_body body;
	}
	[Serializable]
	public class CS_CMD_QUERY_AGENTT_CHILD_body{
		public int userId;
	}
	[Serializable]
	public class CS_CMD_QUERY_AGENTT_CHILD{
		public int cmd;
		public CS_CMD_QUERY_AGENTT_CHILD_body body;
	}
	[Serializable]
	public class AgentInfo{
		public string agentId;
		public int userId;
		public int iLv;
		public int roomcardCnt;
	}
	[Serializable]
	public class SC_CMD_QUERY_AGENTT_CHILD_body{
		public AgentInfo[] agentList;
	}
	[Serializable]
	public class SC_CMD_QUERY_AGENTT_CHILD{
		public int cmd;
		public SC_CMD_QUERY_AGENTT_CHILD_body body;
	}
	[Serializable]
	public class CS_CMD_REALTIME_INFO_body{
		public int reqType;
		public string begin;
		public string end;
	}
	[Serializable]
	public class CS_CMD_REALTIME_INFO{
		public int cmd;
		public CS_CMD_REALTIME_INFO_body body;
	}
	[Serializable]
	public class DataNode{
		public int dataType;
		public int X;
		public int Y;
	}
	[Serializable]
	public class SC_CMD_REALTIME_INFO_body{
		public int reqType;
		public DataNode[] dataList;
	}
	[Serializable]
	public class SC_CMD_REALTIME_INFO{
		public int cmd;
		public SC_CMD_REALTIME_INFO_body body;
	}
	[Serializable]
	public class SC_CMD_REQUEST_ADMINHOMEPAGE_body{
		public int agentCount;
		public int totalGiveRoomCard;
		public int todayGive;
		public int totalConsume;
		public int todayConsume;
		public int playerRoomCard;
		public int playerCount;
		public int newPlayer;
		public int todayLogin;
		public int stopagentCnt;
	}
	[Serializable]
	public class SC_CMD_REQUEST_ADMINHOMEPAGE{
		public int cmd;
		public SC_CMD_REQUEST_ADMINHOMEPAGE_body body;
	}
	[Serializable]
	public class CS_AGENT_CHG_PASSWD_body{
		public string curPassWd;
		public string newPassWd;
	}
	[Serializable]
	public class CS_AGENT_CHG_PASSWD{
		public int cmd;
		public CS_AGENT_CHG_PASSWD_body body;
	}
	[Serializable]
	public class SC_AGENT_CHG_PASSWD_body{
		public bool result;
		public string errmsg;
	}
	[Serializable]
	public class SC_AGENT_CHG_PASSWD{
		public int cmd;
		public SC_AGENT_CHG_PASSWD_body body;
	}
	[Serializable]
	public class CS_AGENT_LOGOUT{
		public int cmd;
	}
	[Serializable]
	public class SC_AGENT_LOGOUT{
		public int cmd;
	}
	[Serializable]
	public class PlayerInfo{
		public int UserId;
		public string Nickname;
		public int CardNum;
		public int GoldNum;
		public int SignUpTimes;
		public int GameTime;
		public int OnLineTime;
		public int SignUpTime;
		public string SignUpIP;
		public int RegisterTime;
		public string RegisterIp;
	}
	[Serializable]
	public class CS_AGENT_QUERY_ALLCHILDAGENT_body{
		public int reqBegin;
		public int reqCount;
	}
	[Serializable]
	public class CS_AGENT_QUERY_ALLCHILDAGENT{
		public int cmd;
		public CS_AGENT_QUERY_ALLCHILDAGENT_body body;
	}
	[Serializable]
	public class SC_AGENT_QUERY_ALLCHILDAGENT_body{
		public PlayerInfo[] playerList;
	}
	[Serializable]
	public class SC_AGENT_QUERY_ALLCHILDAGENT{
		public int cmd;
		public SC_AGENT_QUERY_ALLCHILDAGENT_body body;
	}
	[Serializable]
	public class CS_QUERY_ALL_PLAYER_body{
		public int reqPage;
	}
	[Serializable]
	public class CS_QUERY_ALL_PLAYER{
		public int cmd;
		public CS_QUERY_ALL_PLAYER_body body;
	}
	[Serializable]
	public class SC_QUERY_ALL_PLAYER_body{
		public int reqPage;
		public PlayerInfo[] playerList;
	}
	[Serializable]
	public class SC_QUERY_ALL_PLAYER{
		public int cmd;
		public SC_QUERY_ALL_PLAYER_body body;
	}
	[Serializable]
	public class CS_SET_AGENT_body{
		public string pAgentId;
		public int userId;
		public string prefix;
		public string key;
	}
	[Serializable]
	public class CS_SET_AGENT{
		public int cmd;
		public CS_SET_AGENT_body body;
	}
	[Serializable]
	public class SC_SET_AGENT_body{
		public bool result;
		public string errmsg;
	}
	[Serializable]
	public class SC_SET_AGENT{
		public int cmd;
		public SC_SET_AGENT_body body;
	}
	[Serializable]
	public class CS_AGENT_LOGIN_body{
		public string id;
		public string passwd;
	}
	[Serializable]
	public class CS_AGENT_LOGIN{
		public int cmd;
		public CS_AGENT_LOGIN_body body;
	}
	[Serializable]
	public class SC_AGENT_LOGIN_body{
		public bool result;
		public string errmsg;
		public int permission;
		public string AgentId;
		public int RemainRoomCard;
		public int userId;
	}
	[Serializable]
	public class SC_AGENT_LOGIN{
		public int cmd;
		public SC_AGENT_LOGIN_body body;
	}
	[Serializable]
	public class CS_AGENT_SEARCH_PLAYER_body{
		public int UserId;
	}
	[Serializable]
	public class CS_AGENT_SEARCH_PLAYER{
		public int cmd;
		public CS_AGENT_SEARCH_PLAYER_body body;
	}
	[Serializable]
	public class SC_AGENT_SEARCH_PLAYER_body{
		public bool result;
		public string errmsg;
		public PlayerInfo player;
		public int selfRemaindRoomCard;
		public int selfDayGiveRoomCard;
	}
	[Serializable]
	public class SC_AGENT_SEARCH_PLAYER{
		public int cmd;
		public SC_AGENT_SEARCH_PLAYER_body body;
	}
	[Serializable]
	public class CS_AGENT_GIVE_ROOMCARD_body{
		public int userId;
		public int value;
		public string reason;
	}
	[Serializable]
	public class CS_AGENT_GIVE_ROOMCARD{
		public int cmd;
		public CS_AGENT_GIVE_ROOMCARD_body body;
	}
	[Serializable]
	public class SC_AGENT_GIVE_ROOMCARD_body{
		public bool result;
		public string errmsg;
	}
	[Serializable]
	public class SC_AGENT_GIVE_ROOMCARD{
		public int cmd;
		public SC_AGENT_GIVE_ROOMCARD_body body;
	}
	[Serializable]
	public class CS_AGENT_QUERY_GIVELOG{
		public int cmd;
	}
	[Serializable]
	public class GiveUnit{
		public int time;
		public int value;
		public int giveId;
		public int BeforGiveValue;
	}
	[Serializable]
	public class SC_AGENT_QUERY_GIVELOG_body{
		public GiveUnit[] giveList;
	}
	[Serializable]
	public class SC_AGENT_QUERY_GIVELOG{
		public int cmd;
		public SC_AGENT_QUERY_GIVELOG_body body;
	}
	[Serializable]
	public class CS_AGENT_QUERY_CONSUMELOG{
		public int cmd;
	}
	[Serializable]
	public class playerRes{
		public string name;
		public int score;
		public string playerId;
	}
	[Serializable]
	public class GameDetail{
		public bool bWin;
		public playerRes[] playerList;
	}
	[Serializable]
	public class ConsumeLog{
		public string time;
		public int value;
		public int roomId;
		public GameDetail detail;
	}
	[Serializable]
	public class SC_AGENT_QUERY_CONSUMELOG_body{
		public ConsumeLog[] cosumeList;
	}
	[Serializable]
	public class SC_AGENT_QUERY_CONSUMELOG{
		public int cmd;
		public SC_AGENT_QUERY_CONSUMELOG_body body;
	}

}