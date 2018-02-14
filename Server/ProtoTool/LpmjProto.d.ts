declare namespace LpmjProto{
	enum command {
		enum=1,
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
	enum enHuType {
		enum=1,
		enHuType_ZiMo=1,
		enHuType_JiePao=2,
		enHuType_QiangGang=3,
	}
	enum enHuKind {
		enum=1,
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
	enum enActionMask {
		enum=1,
		enActionMask_NULL=0,
		enActionMask_Chi=1,
		enActionMask_Peng=2,
		enActionMask_Gang=4,
		enActionMask_Hu=8,
	}
	export interface LpmjPrivateRule{
		isLimit:boolean;
		limitScore:number;
	}
	export interface SC_SUBS_GAME_REMOVEDISCARD{
		chair:number;
	}
	export interface SC_SUBS_GAME_START{
		bankUser:number;
		sliceCount:number[];
		tail:number;
		magicIndex:number;
		szCardList:number[];
		curTurn:number;
		totalTurn:number;
	}
	export interface SC_GAME_SCENE_BODY{
	}
	export interface TingDetail{
		outcard:number;
		szCardList:number[];
	}
	export interface SC_SUBS_OPERATE_NOTIFY{
		operateMask:number;
		isOwnTake:boolean;
		operateCard:number;
		szSelfGangList:number[];
		szTingList:TingDetail[];
		chiList:number[];
	}
	export interface CS_SUBS_GAME_POPCARD{
		outCard:number;
	}
	export interface SC_SUBS_GAME_POPCARD{
		userChair:number;
		outCard:number;
	}
	export interface SC_SUBS_GAME_PUSHCARD{
		userChair:number;
		card:number;
		isTail:boolean;
	}
	export interface PlayerConcludeInfo{
		chair:number;
		huType:number;
		huKindMask:number;
		huScore:number;
		baoScore:number;
		resultScore:number;
		cardGroupList:CardGroup[];
		handCardList:number[];
	}
	export interface SC_SUBS_GAME_CONCLUDE{
		totalGameCnt:number;
		finishGameCnt:number;
		huCard:number;
		huProvide:number;
		resultList:PlayerConcludeInfo[];
	}
	export interface PlayerGameRecord{
		chair:number;
		isOwner:boolean;
		zimoCnt:number;
		jiepaoCnt:number;
		dianpaoCnt:number;
		dabaoCnt:number;
		isBigWin:boolean;
		isBigPao:boolean;
		totalScore:number;
	}
	export interface SC_SUBS_GAME_RECORD{
		szRecordList:PlayerGameRecord[];
	}
	export interface CS_SUBS_GAME_OPERATE{
		operate:number;
		gangCard:number;
		chiList:number[];
	}
	export interface SC_SUBS_GAME_OPERATE{
		chair:number;
		operate:number;
		operateCard:number;
		chiList:number[];
		leftHandCardCnt:number;
		isAnGang:boolean;
	}
	export interface ScoreInfo{
		chair:number;
		score:number;
	}
	export interface GameSceneStatusFree{
		scoreList:ScoreInfo[];
	}
	export interface CardGroup{
		groupType:number;
		isAnGang:boolean;
		cardList:number[];
		chiCard:number;
	}
	export interface PlayerInGameInfo{
		chiar:number;
		discardList:number[];
		cardGroupList:CardGroup[];
		handCardList:number[];
		handCardCount:number;
		score:number;
	}
	export interface GameSceneStatusPlay{
		bankUser:number;
		magicIndex:number;
		operateInfo:SC_SUBS_OPERATE_NOTIFY;
		leftcardcnt:number;
		curUser:number;
		popCard:number;
		lastDiscardUser:number;
		playerInfoList:PlayerInGameInfo[];
	}
	export interface SC_SUBS_GAME_SCENE{
		isInGame:boolean;
		curTurn:number;
		totoalTurn:number;
		statusFree:GameSceneStatusFree;
		statusPlay:GameSceneStatusPlay;
	}
	export interface SC_SUBS_GAME_ADDDISCARD{
		chair:number;
		card:number;
	}

}