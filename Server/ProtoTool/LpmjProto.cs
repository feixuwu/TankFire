using UnityEngine; 
using System; 
namespace LpmjProto{
	public enum command {
		SUBS_GAME_START=1,
		SUBS_GAME_POPCARD=2,
		SUBS_GAME_PUSHCARD=3,
		SUBS_OPERATE_NOTIFY=4,
		SUBS_GAME_CONCLUDE=5,
		SUBS_GAME_RECORD=6,
		SUBS_GAME_OPERATE=7,
		SUBS_GAME_SCENE=8,
		SUBS_GAME_ADDDISCARD=9,
		SUBS_GAME_REMOVEDISCARD=10,
	}
	public enum enHuType {
		enHuType_ZiMo=1,
		enHuType_JiePao=2,
		enHuType_QiangGang=3,
	}
	public enum enHuKind {
		enHuKind_Ping=1,
		enHuKind_QiDui=2,
		enHuKind_PengPengHu=4,
		enHuKind_ShiSanLan=8,
		enHuKind_QiZiQuan=16,
		enHuKind_HunYiSe=32,
		enHuKind_QinYiSe=64,
		enHuKind_ZiYiSe=128,
		enHuKind_GangKai=256,
		enHuKind_QiangGang=512,
		enHuKind_WuBao=1024,
		enHuKind_TianHu=2048,
		enHuKind_DiHu=4096,
		enHuKind_SiBao=8192,
	}
	public enum enActionMask {
		enActionMask_NULL=0,
		enActionMask_Chi=1,
		enActionMask_Peng=2,
		enActionMask_Gang=4,
		enActionMask_Hu=8,
	}
	[Serializable]
	public class LpmjPrivateRule{
		public bool isLimit;
		public int limitScore;
	}
	[Serializable]
	public class SC_SUBS_GAME_REMOVEDISCARD{
		public int chair;
	}
	[Serializable]
	public class SC_SUBS_GAME_START{
		public int bankUser;
		public int[] sliceCount;
		public int tail;
		public int magicIndex;
		public int[] szCardList;
		public int curTurn;
		public int totalTurn;
	}
	[Serializable]
	public class SC_GAME_SCENE_BODY{
	}
	[Serializable]
	public class TingDetail{
		public int outcard;
		public int[] szCardList;
	}
	[Serializable]
	public class SC_SUBS_OPERATE_NOTIFY{
		public int operateMask;
		public bool isOwnTake;
		public int operateCard;
		public int[] szSelfGangList;
		public TingDetail[] szTingList;
		public int[] chiList;
	}
	[Serializable]
	public class CS_SUBS_GAME_POPCARD{
		public int outCard;
	}
	[Serializable]
	public class SC_SUBS_GAME_POPCARD{
		public int userChair;
		public int outCard;
	}
	[Serializable]
	public class SC_SUBS_GAME_PUSHCARD{
		public int userChair;
		public int card;
		public bool isTail;
	}
	[Serializable]
	public class PlayerConcludeInfo{
		public int chair;
		public int huType;
		public int huKindMask;
		public int huScore;
		public int baoScore;
		public int resultScore;
		public CardGroup[] cardGroupList;
		public int[] handCardList;
	}
	[Serializable]
	public class SC_SUBS_GAME_CONCLUDE{
		public int totalGameCnt;
		public int finishGameCnt;
		public int huCard;
		public int huProvide;
		public PlayerConcludeInfo[] resultList;
	}
	[Serializable]
	public class PlayerGameRecord{
		public int chair;
		public bool isOwner;
		public int zimoCnt;
		public int jiepaoCnt;
		public int dianpaoCnt;
		public int dabaoCnt;
		public bool isBigWin;
		public bool isBigPao;
		public int totalScore;
	}
	[Serializable]
	public class SC_SUBS_GAME_RECORD{
		public PlayerGameRecord[] szRecordList;
	}
	[Serializable]
	public class CS_SUBS_GAME_OPERATE{
		public int operate;
		public int gangCard;
		public int[] chiList;
	}
	[Serializable]
	public class SC_SUBS_GAME_OPERATE{
		public int chair;
		public int operate;
		public int operateCard;
		public int[] chiList;
		public int leftHandCardCnt;
		public bool isAnGang;
	}
	[Serializable]
	public class ScoreInfo{
		public int chair;
		public int score;
	}
	[Serializable]
	public class GameSceneStatusFree{
		public ScoreInfo[] scoreList;
	}
	[Serializable]
	public class CardGroup{
		public int groupType;
		public bool isAnGang;
		public int[] cardList;
		public int chiCard;
	}
	[Serializable]
	public class PlayerInGameInfo{
		public int chiar;
		public int[] discardList;
		public CardGroup[] cardGroupList;
		public int[] handCardList;
		public int handCardCount;
		public int score;
	}
	[Serializable]
	public class GameSceneStatusPlay{
		public int bankUser;
		public int magicIndex;
		public SC_SUBS_OPERATE_NOTIFY operateInfo;
		public int leftcardcnt;
		public int curUser;
		public int popCard;
		public int lastDiscardUser;
		public PlayerInGameInfo[] playerInfoList;
	}
	[Serializable]
	public class SC_SUBS_GAME_SCENE{
		public bool isInGame;
		public int curTurn;
		public int totoalTurn;
		public GameSceneStatusFree statusFree;
		public GameSceneStatusPlay statusPlay;
	}
	[Serializable]
	public class SC_SUBS_GAME_ADDDISCARD{
		public int chair;
		public int card;
	}

}