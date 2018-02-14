using UnityEngine; 
using System; 
namespace GameProto{
	public enum command {
		CMD_SENDCARD=1,
		CMD_SHOWARD=2,
		CMD_COMPARE=3,
		CMD_MATCH_CARDS=4,
		CMD_ONE_KEY_BAIPAI=5,
		CMD_CHECK_BAIPAI=6,
		CMD_GAME_OVER=7,
		CMD_GAME_SCENE_INFO=8,
		CMD_QUERY_NOTICE=9,
	}
	public enum enCardType {
		CT_INVALID=0,
		CT_SINGLE=1,
		CT_1DOUBLE=2,
		CT_2DOUBLE=3,
		CT_3T=4,
		CT_5STRAIGHT=5,
		CT_5FLUSH=6,
		CT_3T_1DOUBLE=7,
		CT_4T_SINGLE=8,
		CT_5STRAIGHT_FLUSH=9,
		CT_EX_INVALID=10,
		CT_EX_SANTONGHUA=11,
		CT_EX_SANSHUNZI=12,
		CT_EX_LIUDUIBAN=13,
	}
	public enum enCardType_Extra {
		FIRST_CT_3T=1,
		MID_CT_3T_1DOUBLE=2,
		MID_CT_4T_SINGLE=3,
		MID_CT_5STRAIGHT_FLUSH=4,
		LAST_CT_4T_SINGLE=5,
		LAST_CT_5STRAIGHT_FLUSH=6,
		DA_QIANG=7,
		HONG_BO_LANG=8,
		HONG_BO_LANG_FIRST_CT_3T=9,
		MING_PAI_HONG_BO_LANG=10,
		MA_PAI=11,
	}
	public enum enShowType {
		enShowType_QUEREN=1,
		enShowType_MINGPAI=2,
		enShowType_NOCHANGE=3,
		enShowType_MINPAIRESET=4,
		enShowType_WAIT=5,
		enShowType_MINPAIRESET_RESUME=6,
	}
	public enum enDao {
		SHOU_DAO=1,
		ZHONG_DAO=2,
		WEI_DAO=3,
		XIAPAI_SHOU_DAO=4,
		XIAPAI_ZHONG_DAO=5,
		XIAPAI_WEI_DAO=6,
	}
	[Serializable]
	public class MemberPrivate{
		public int iCharId;
		public int iScore;
	}
	[Serializable]
	public class SC_CMD_GAME_SCENE_INFO_body{
		public int iCurTurn;
		public MemberPrivate[] memeberList;
	}
	[Serializable]
	public class SC_CMD_GAME_SCENE_INFO{
		public int cmd;
		public SC_CMD_GAME_SCENE_INFO_body body;
	}
	[Serializable]
	public class PrivateRule{
		public bool bIsMingPai;
		public bool bHasHorse;
		public int horseCardId;
	}
	[Serializable]
	public class CardUnit{
		public int[] list;
	}
	[Serializable]
	public class FilterCardMsg{
		public int type;
		public CardUnit[] cardList;
	}
	[Serializable]
	public class SC_CMD_SENDCARD_body{
		public bool result;
		public string id;
		public int chairId;
		public int[] cardData;
		public FilterCardMsg[] filterCardList;
	}
	[Serializable]
	public class SC_CMD_SENDCARD{
		public int cmd;
		public SC_CMD_SENDCARD_body body;
	}
	[Serializable]
	public class CS_CMD_SHOWCARD_body{
		public int[] firstList;
		public int[] middleList;
		public int[] lastList;
		public int showType;
	}
	[Serializable]
	public class CS_CMD_SHOWCARD{
		public int cmd;
		public CS_CMD_SHOWCARD_body body;
	}
	[Serializable]
	public class PlayerDaoList{
		public int chairId;
		public int[] firstList;
		public int[] middleList;
		public int[] lastList;
	}
	[Serializable]
	public class SC_CMD_SHOWCARD_body{
		public int iCharId;
		public bool result;
		public int showType;
		public PlayerDaoList[] MinPaiList;
		public PlayerDaoList selfDao;
	}
	[Serializable]
	public class SC_CMD_SHOWCARD{
		public int cmd;
		public SC_CMD_SHOWCARD_body body;
	}
	[Serializable]
	public class DaoRes{
		public int[] cardList;
		public int iScore;
		public int cardType;
	}
	[Serializable]
	public class PlayerCompareRes{
		public int chairId;
		public DaoRes[] resList;
		public int iTotalScore;
		public int[] daqiangList;
		public bool hongbolang;
		public bool bIsMinPai;
	}
	[Serializable]
	public class SC_CMD_COMPARE_body{
		public PlayerCompareRes[] compareSeq;
	}
	[Serializable]
	public class SC_CMD_COMPARE{
		public int cmd;
		public SC_CMD_COMPARE_body body;
	}
	[Serializable]
	public class SC_CMD_MATCH_CARDS_body{
		public int[] firstList;
		public int[] middleList;
		public int[] lastList;
	}
	[Serializable]
	public class SC_CMD_MATCH_CARDS{
		public int cmd;
		public SC_CMD_MATCH_CARDS_body body;
	}
	[Serializable]
	public class CS_CMD_ONE_KEY_BAIPAI{
		public int cmd;
	}
	[Serializable]
	public class SC_CMD_ONE_KEY_BAIPAI_body{
		public int[] firstList;
		public int[] middleList;
		public int[] lastList;
	}
	[Serializable]
	public class SC_CMD_ONE_KEY_BAIPAI{
		public int cmd;
		public SC_CMD_ONE_KEY_BAIPAI_body body;
	}
	[Serializable]
	public class CS_CMD_CHECK_BAIPAI_body{
		public int[] firstList;
		public int[] middleList;
		public int[] lastList;
		public int curDao;
	}
	[Serializable]
	public class CS_CMD_CHECK_BAIPAI{
		public int cmd;
		public CS_CMD_CHECK_BAIPAI_body body;
	}
	[Serializable]
	public class SC_CMD_CHECK_BAIPAI_body{
		public int[] firstList;
		public int[] middleList;
		public int[] lastList;
		public bool bIsDaoShui;
		public FilterCardMsg[] filterCardList;
		public int curDao;
	}
	[Serializable]
	public class SC_CMD_CHECK_BAIPAI{
		public int cmd;
		public SC_CMD_CHECK_BAIPAI_body body;
	}
	[Serializable]
	public class CS_CMD_QUERY_NOTICE{
		public int cmd;
	}
	[Serializable]
	public class SC_CMD_QUERY_NOTICE_body{
		public FilterCardMsg[] filterCardList;
	}
	[Serializable]
	public class SC_CMD_QUERY_NOTICE{
		public int cmd;
		public SC_CMD_QUERY_NOTICE_body body;
	}
	[Serializable]
	public class PlayerGameInfo{
		public int chairId;
		public int winCount;
		public int loseCount;
		public int peaceCount;
		public int totalScore;
	}
	[Serializable]
	public class SC_CMD_GAME_OVER_body{
		public PlayerGameInfo[] playerGameResList;
	}
	[Serializable]
	public class SC_CMD_GAME_OVER{
		public int cmd;
		public SC_CMD_GAME_OVER_body body;
	}

}