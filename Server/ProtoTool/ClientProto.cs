using UnityEngine; 
using System; 
namespace ClientProto{
	public enum command {
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
		CMD_QUERY_GAMECONFIG=13,
		CMD_PLAYER_OFFLINE=14,
		CMD_DISMISS_ROOM_AGREE=15,
		CMD_ROOM_DISMISS=16,
		CMD_CHAT=17,
		CMD_ASSET_CHG=18,
		CMD_AGENT_QUERY=19,
		CMD_AGENT_CODE=20,
		CMD_QUERY_GAMERECORD=21,
		CMD_QUERY_SHOP=22,
		CMD_GENERATE_ORDER=23,
		CMD_REFRESH_ASSET=24,
	}
	public enum enChgType {
		enChgType_RoomCard=1,
		enChgType_Gold=2,
	}
	public enum enChatType {
		enChatType_default=1,
		enChatType_Text=2,
		enChatType_Image=3,
		enChatType_Voice=4,
	}
	public enum enGameMode {
		enComsumeMode_VIP=0,
		enComsumeMode_Card=1,
	}
	public enum PayWay {
		Pay_RoomOwner=0,
		Pay_AA=1,
	}
	public enum enSex {
		enSex_Boy=1,
		enSex_Girl=2,
	}
	public enum enChoose {
		enChoose_Agree=1,
		enChoose_Refuse=2,
		enChoose_Wait=3,
	}
	[Serializable]
	public class CS_CMD_REFRESH_ASSET{
		public int cmd;
	}
	[Serializable]
	public class SC_CMD_REFRESH_ASSET_body{
		public int viptime;
		public int roomcard;
	}
	[Serializable]
	public class SC_CMD_REFRESH_ASSET{
		public int cmd;
		public SC_CMD_REFRESH_ASSET_body body;
	}
	[Serializable]
	public class SC_CMD_GENERATE_ORDER_body{
		public int itemId;
		public string orderID;
	}
	[Serializable]
	public class SC_CMD_GENERATE_ORDER{
		public int cmd;
		public SC_CMD_GENERATE_ORDER_body body;
	}
	[Serializable]
	public class CS_CMD_GENERATE_ORDER_body{
		public int itemId;
	}
	[Serializable]
	public class CS_CMD_GENERATE_ORDER{
		public int cmd;
		public CS_CMD_GENERATE_ORDER_body body;
	}
	[Serializable]
	public class ShopConfigItem{
		public int itemID;
		public string itemSubject;
		public string itemText;
		public int price;
		public int discountprice;
		public string addtionText;
	}
	[Serializable]
	public class SC_CMD_QUERY_SHOP_body{
		public bool isPayed;
		public ShopConfigItem[] itemList;
	}
	[Serializable]
	public class SC_CMD_QUERY_SHOP{
		public int cmd;
		public SC_CMD_QUERY_SHOP_body body;
	}
	[Serializable]
	public class CS_CMD_QUERY_SHOP{
		public int cmd;
	}
	[Serializable]
	public class CS_CMD_QUERY_GAMERECORD_body{
		public int gameid;
	}
	[Serializable]
	public class CS_CMD_QUERY_GAMERECORD{
		public int cmd;
		public CS_CMD_QUERY_GAMERECORD_body body;
	}
	[Serializable]
	public class GameRecordPlayerScore{
		public string playerName;
		public int score;
	}
	[Serializable]
	public class GameRecordItem{
		public string roomid;
		public string time;
		public GameRecordPlayerScore[] scoreList;
		public bool isWin;
	}
	[Serializable]
	public class GameRecordSaveDB{
		public GameRecordItem[] recordList;
	}
	[Serializable]
	public class SC_CMD_QUERY_GAMERECORD_body{
		public GameRecordItem[] recordList;
	}
	[Serializable]
	public class SC_CMD_QUERY_GAMERECORD{
		public int cmd;
		public SC_CMD_QUERY_GAMERECORD_body body;
	}
	[Serializable]
	public class CS_CMD_AGENT_QUERY{
		public int cmd;
	}
	[Serializable]
	public class SC_CMD_AGENT_QUERY_body{
		public string content;
	}
	[Serializable]
	public class SC_CMD_AGENT_QUERY{
		public int cmd;
		public SC_CMD_AGENT_QUERY_body body;
	}
	[Serializable]
	public class CS_CMD_AGENT_CODE_body{
		public string agentCode;
	}
	[Serializable]
	public class CS_CMD_AGENT_CODE{
		public int cmd;
		public CS_CMD_AGENT_CODE_body body;
	}
	[Serializable]
	public class SC_CMD_AGENT_CODE_body{
		public bool result;
		public string errmsg;
	}
	[Serializable]
	public class SC_CMD_AGENT_CODE{
		public int cmd;
		public SC_CMD_AGENT_CODE_body body;
	}
	[Serializable]
	public class SC_CMD_ASSET_CHG_body{
		public int chgType;
		public int chgVal;
	}
	[Serializable]
	public class SC_CMD_ASSET_CHG{
		public int cmd;
		public SC_CMD_ASSET_CHG_body body;
	}
	[Serializable]
	public class chatContent{
		public int type;
		public string tent;
	}
	[Serializable]
	public class CS_CMD_CHAT_body{
		public chatContent content;
	}
	[Serializable]
	public class CS_CMD_CHAT{
		public int cmd;
		public CS_CMD_CHAT_body body;
	}
	[Serializable]
	public class SC_CMD_CHAT_body{
		public string playerId;
		public chatContent content;
	}
	[Serializable]
	public class SC_CMD_CHAT{
		public int cmd;
		public SC_CMD_CHAT_body body;
	}
	[Serializable]
	public class CS_CMD_LOGIN_body{
		public string account;
		public string password;
		public string accesstoken;
		public string openid;
	}
	[Serializable]
	public class CS_CMD_LOGIN{
		public int cmd;
		public CS_CMD_LOGIN_body body;
	}
	[Serializable]
	public class AccountBaseInfo{
		public string account;
		public string name;
		public string id;
		public string icon;
		public int card;
		public int vipTime;
	}
	[Serializable]
	public class SC_CMD_LOGIN_body{
		public bool result;
		public AccountBaseInfo data;
		public string errmsg;
	}
	[Serializable]
	public class SC_CMD_LOGIN{
		public int cmd;
		public SC_CMD_LOGIN_body body;
	}
	[Serializable]
	public class CS_CMD_REGISTER_body{
		public string account;
		public string password;
	}
	[Serializable]
	public class CS_CMD_REGISTER{
		public int cmd;
		public CS_CMD_REGISTER_body body;
	}
	[Serializable]
	public class SC_CMD_REGISTER_body{
		public bool result;
	}
	[Serializable]
	public class SC_CMD_REGISTER{
		public int cmd;
		public SC_CMD_REGISTER_body body;
	}
	[Serializable]
	public class GameDefineInfo{
		public string gameid;
		public string name;
	}
	[Serializable]
	public class SC_CMD_GAMELIST_body{
		public GameDefineInfo[] gamelist;
	}
	[Serializable]
	public class SC_CMD_GAMELIST{
		public int cmd;
		public SC_CMD_GAMELIST_body body;
	}
	[Serializable]
	public class ServerInfo{
		public string id;
		public string host;
		public int port;
		public GameDefineInfo[] gamelist;
	}
	[Serializable]
	public class SC_CMD_SERVERLIST_body{
		public ServerInfo[] serverlist;
	}
	[Serializable]
	public class SC_CMD_SERVERLIST{
		public int cmd;
		public SC_CMD_SERVERLIST_body body;
	}
	[Serializable]
	public class CS_CMD_QUERY_GAMECONFIG_body{
		public string gameid;
		public int mode;
	}
	[Serializable]
	public class CS_CMD_QUERY_GAMECONFIG{
		public int cmd;
		public CS_CMD_QUERY_GAMECONFIG_body body;
	}
	[Serializable]
	public class GameConfigInfo{
		public int gamecount;
		public int cost;
	}
	[Serializable]
	public class SC_CMD_QUERY_GAMECONFIG_body{
		public string gameid;
		public bool result;
		public int minplayercnt;
		public int maxplayercnt;
		public GameConfigInfo[] configList;
		public string errmsg;
	}
	[Serializable]
	public class SC_CMD_QUERY_GAMECONFIG{
		public int cmd;
		public SC_CMD_QUERY_GAMECONFIG_body body;
	}
	[Serializable]
	public class CS_CMD_CREATE_ROOM_body{
		public string gameid;
		public int mode;
		public int gamecount;
		public int playercount;
		public int payWay;
		public string privaterule;
	}
	[Serializable]
	public class CS_CMD_CREATE_ROOM{
		public int cmd;
		public CS_CMD_CREATE_ROOM_body body;
	}
	[Serializable]
	public class RoomMember{
		public string name;
		public string id;
		public string ip;
		public int chair;
		public bool bReady;
		public string icon;
		public int sex;
	}
	[Serializable]
	public class RoomDetail{
		public RoomMember[] memberlist;
		public string ownerid;
		public string gameid;
		public string roomid;
		public int playercount;
		public int gamecount;
		public string privaterule;
		public bool isstarted;
		public int payWay;
	}
	[Serializable]
	public class SC_CMD_CREATE_ROOM_body{
		public bool result;
		public RoomDetail roominfo;
		public string error;
	}
	[Serializable]
	public class SC_CMD_CREATE_ROOM{
		public int cmd;
		public SC_CMD_CREATE_ROOM_body body;
	}
	[Serializable]
	public class CS_CMD_JOIN_ROOM_body{
		public string roomid;
	}
	[Serializable]
	public class CS_CMD_JOIN_ROOM{
		public int cmd;
		public CS_CMD_JOIN_ROOM_body body;
	}
	[Serializable]
	public class SC_CMD_JOIN_ROOM_body{
		public bool result;
		public RoomDetail roominfo;
		public string error;
		public bool bInGame;
	}
	[Serializable]
	public class SC_CMD_JOIN_ROOM{
		public int cmd;
		public SC_CMD_JOIN_ROOM_body body;
	}
	[Serializable]
	public class CS_CMD_LEAVE_ROOM{
		public int cmd;
	}
	[Serializable]
	public class SC_CMD_LEAVE_ROOM_body{
		public string userid;
		public string error;
		public int remain;
	}
	[Serializable]
	public class SC_CMD_LEAVE_ROOM{
		public int cmd;
		public SC_CMD_LEAVE_ROOM_body body;
	}
	[Serializable]
	public class CS_CMD_DISMISS_ROOM_AGREE_body{
		public bool bAgree;
	}
	[Serializable]
	public class CS_CMD_DISMISS_ROOM_AGREE{
		public int cmd;
		public CS_CMD_DISMISS_ROOM_AGREE_body body;
	}
	[Serializable]
	public class LeaveChoose{
		public string userid;
		public int chooseState;
	}
	[Serializable]
	public class SC_CMD_DISMISS_ROOM_AGREE_body{
		public LeaveChoose[] chooseList;
		public int remaindSec;
		public string applyUserId;
	}
	[Serializable]
	public class SC_CMD_DISMISS_ROOM_AGREE{
		public int cmd;
		public SC_CMD_DISMISS_ROOM_AGREE_body body;
	}
	[Serializable]
	public class SC_CMD_ROOM_DISMISS_body{
		public bool result;
	}
	[Serializable]
	public class SC_CMD_ROOM_DISMISS{
		public int cmd;
		public SC_CMD_ROOM_DISMISS_body body;
	}
	[Serializable]
	public class CS_CMD_GAME_REAY{
		public int cmd;
	}
	[Serializable]
	public class SC_CMD_GAME_REAY_body{
		public bool result;
		public string userid;
		public string error;
	}
	[Serializable]
	public class SC_CMD_GAME_REAY{
		public int cmd;
		public SC_CMD_GAME_REAY_body body;
	}
	[Serializable]
	public class SC_CMD_GAME_START_body{
		public string privatedata;
	}
	[Serializable]
	public class SC_CMD_GAME_START{
		public int cmd;
		public SC_CMD_GAME_START_body body;
	}
	[Serializable]
	public class SC_CMD_GAME_SENDSCENE_body{
		public string privatedata;
	}
	[Serializable]
	public class SC_CMD_GAME_SENDSCENE{
		public int cmd;
		public SC_CMD_GAME_SENDSCENE_body body;
	}
	[Serializable]
	public class CS_CMD_GAME_MESSAGE_body{
		public string privatedata;
	}
	[Serializable]
	public class CS_CMD_GAME_MESSAGE{
		public int cmd;
		public int subcmd;
		public CS_CMD_GAME_MESSAGE_body body;
	}
	[Serializable]
	public class SC_CMD_GAME_MESSAGE_body{
		public string privatedata;
	}
	[Serializable]
	public class SC_CMD_GAME_MESSAGE{
		public int cmd;
		public int subcmd;
		public SC_CMD_GAME_MESSAGE_body body;
	}
	[Serializable]
	public class SC_CMD_NOTIFY_CURROOM_body{
		public bool existroom;
		public RoomDetail[] roomlist;
	}
	[Serializable]
	public class SC_CMD_NOTIFY_CURROOM{
		public int cmd;
		public SC_CMD_NOTIFY_CURROOM_body body;
	}
	[Serializable]
	public class SC_CMD_PLAYER_OFFLINE_body{
		public string userid;
	}
	[Serializable]
	public class SC_CMD_PLAYER_OFFLINE{
		public int cmd;
		public SC_CMD_PLAYER_OFFLINE_body body;
	}

}