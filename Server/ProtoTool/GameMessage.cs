using UnityEngine; 
using System; 
namespace GameMessage{
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
	}
	public enum enGameMode {
		enComsumeMode_VIP=0,
		enComsumeMode_Card=1,
	}
	[Serializable]
	public struct CS_CMD_LOGIN_body{
		public string account;
		public string password;
	}
	[Serializable]
	public struct CS_CMD_LOGIN{
		public int cmd;
		public CS_CMD_LOGIN_body body;
	}
	[Serializable]
	public struct AccountBaseInfo{
		public string account;
		public string name;
		public string id;
		public string icon;
	}
	[Serializable]
	public struct SC_CMD_LOGIN_body{
		public bool result;
		public AccountBaseInfo data;
		public string errmsg;
	}
	[Serializable]
	public struct SC_CMD_LOGIN{
		public int cmd;
		public SC_CMD_LOGIN_body body;
	}
	[Serializable]
	public struct CS_CMD_REGISTER_body{
		public string account;
		public string password;
	}
	[Serializable]
	public struct CS_CMD_REGISTER{
		public int cmd;
		public CS_CMD_REGISTER_body body;
	}
	[Serializable]
	public struct SC_CMD_REGISTER_body{
		public bool result;
	}
	[Serializable]
	public struct SC_CMD_REGISTER{
		public int cmd;
		public SC_CMD_REGISTER_body body;
	}
	[Serializable]
	public struct GameDefineInfo{
		public string gameid;
		public string name;
	}
	[Serializable]
	public struct SC_CMD_GAMELIST_body{
		public GameDefineInfo[] gamelist;
	}
	[Serializable]
	public struct SC_CMD_GAMELIST{
		public int cmd;
		public SC_CMD_GAMELIST_body body;
	}
	[Serializable]
	public struct ServerInfo{
		public string id;
		public string host;
		public int port;
		public GameDefineInfo[] gamelist;
	}
	[Serializable]
	public struct SC_CMD_SERVERLIST_body{
		public ServerInfo[] serverlist;
	}
	[Serializable]
	public struct SC_CMD_SERVERLIST{
		public int cmd;
		public SC_CMD_SERVERLIST_body body;
	}
	[Serializable]
	public struct CS_CMD_CREATE_ROOM_body{
		public string gameid;
		public int mode;
		public int gamecount;
		public int playercount;
		public string privaterule;
	}
	[Serializable]
	public struct CS_CMD_CREATE_ROOM{
		public int cmd;
		public CS_CMD_CREATE_ROOM_body body;
	}
	[Serializable]
	public struct RoomMember{
		public string name;
		public string id;
		public string ip;
		public int chair;
	}
	[Serializable]
	public struct RoomDetail{
		public RoomMember[] memberlist;
		public string ownerid;
		public string gameid;
		public string roomid;
		public int playercount;
		public int gamecount;
		public string privaterule;
		public bool isstarted;
	}
	[Serializable]
	public struct SC_CMD_CREATE_ROOM_body{
		public bool result;
		public RoomDetail roominfo;
		public string error;
	}
	[Serializable]
	public struct SC_CMD_CREATE_ROOM{
		public int cmd;
		public SC_CMD_CREATE_ROOM_body body;
	}
	[Serializable]
	public struct CS_CMD_JOIN_ROOM_body{
		public string roomid;
	}
	[Serializable]
	public struct CS_CMD_JOIN_ROOM{
		public int cmd;
		public CS_CMD_JOIN_ROOM_body body;
	}
	[Serializable]
	public struct SC_CMD_JOIN_ROOM_body{
		public bool result;
		public RoomDetail roominfo;
		public string error;
	}
	[Serializable]
	public struct SC_CMD_JOIN_ROOM{
		public int cmd;
		public SC_CMD_JOIN_ROOM_body body;
	}
	[Serializable]
	public struct CS_CMD_LEAVE_ROOM{
		public int cmd;
	}
	[Serializable]
	public struct SC_CMD_LEAVE_ROOM_body{
		public bool result;
		public string userid;
		public string error;
	}
	[Serializable]
	public struct SC_CMD_LEAVE_ROOM{
		public int cmd;
		public SC_CMD_LEAVE_ROOM_body body;
	}
	[Serializable]
	public struct CS_CMD_GAME_REAY{
		public int cmd;
	}
	[Serializable]
	public struct SC_CMD_GAME_REAY_body{
		public bool result;
		public string userid;
		public string error;
	}
	[Serializable]
	public struct SC_CMD_GAME_REAY{
		public int cmd;
		public SC_CMD_GAME_REAY_body body;
	}
	[Serializable]
	public struct SC_CMD_GAME_START_body{
		public string privatedata;
	}
	[Serializable]
	public struct SC_CMD_GAME_START{
		public int cmd;
		public SC_CMD_GAME_START_body body;
	}
	[Serializable]
	public struct SC_CMD_GAME_SENDSCENE_body{
		public string privatedata;
	}
	[Serializable]
	public struct SC_CMD_GAME_SENDSCENE{
		public int cmd;
		public SC_CMD_GAME_SENDSCENE_body body;
	}
	[Serializable]
	public struct CS_CMD_GAME_MESSAGE_body{
		public string privatedata;
	}
	[Serializable]
	public struct CS_CMD_GAME_MESSAGE{
		public int cmd;
		public int subcmd;
		public CS_CMD_GAME_MESSAGE_body body;
	}
	[Serializable]
	public struct SC_CMD_GAME_MESSAGE_body{
		public string privatedata;
	}
	[Serializable]
	public struct SC_CMD_GAME_MESSAGE{
		public int cmd;
		public int subcmd;
		public SC_CMD_GAME_MESSAGE_body body;
	}
	[Serializable]
	public struct SC_CMD_NOTIFY_CURROOM_body{
		public bool existroom;
		public RoomDetail[] roomlist;
	}
	[Serializable]
	public struct SC_CMD_NOTIFY_CURROOM{
		public int cmd;
		public SC_CMD_NOTIFY_CURROOM_body body;
	}

}