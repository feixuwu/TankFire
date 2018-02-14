declare namespace GSProto{
	enum command {
		enum=1,
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
	enum enCardType {
		enum=1,
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
	enum enCardType_Extra {
		enum=1,
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
	enum enShowType {
		enum=1,
		enShowType_QUEREN=1,
		enShowType_MINGPAI=2,
		enShowType_NOCHANGE=3,
		enShowType_MINPAIRESET=4,
		enShowType_WAIT=5,
		enShowType_MINPAIRESET_RESUME=6,
	}
	enum enDao {
		enum=1,
		SHOU_DAO=1,
		ZHONG_DAO=2,
		WEI_DAO=3,
		XIAPAI_SHOU_DAO=4,
		XIAPAI_ZHONG_DAO=5,
		XIAPAI_WEI_DAO=6,
	}
	export interface MemberPrivate{
		iCharId:number;
		iScore:number;
	}
	export interface SC_CMD_GAME_SCENE_INFO_body{
		iCurTurn:number;
		memeberList:MemberPrivate[];
	}
	export interface SC_CMD_GAME_SCENE_INFO{
		cmd:number;
		body:SC_CMD_GAME_SCENE_INFO_body;
	}
	export interface PrivateRule{
		bIsMingPai:boolean;
		bHasHorse:boolean;
		horseCardId:number;
	}
	export interface CardUnit{
		list:number[];
	}
	export interface FilterCardMsg{
		type:number;
		cardList:CardUnit[];
	}
	export interface SC_CMD_SENDCARD_body{
		result:boolean;
		id:string;
		chairId:number;
		cardData:number[];
		filterCardList:FilterCardMsg[];
	}
	export interface SC_CMD_SENDCARD{
		cmd:number;
		body:SC_CMD_SENDCARD_body;
	}
	export interface CS_CMD_SHOWCARD_body{
		firstList:number[];
		middleList:number[];
		lastList:number[];
		showType:number;
	}
	export interface CS_CMD_SHOWCARD{
		cmd:number;
		body:CS_CMD_SHOWCARD_body;
	}
	export interface PlayerDaoList{
		chairId:number;
		firstList:number[];
		middleList:number[];
		lastList:number[];
	}
	export interface SC_CMD_SHOWCARD_body{
		iCharId:number;
		result:boolean;
		showType:number;
		MinPaiList:PlayerDaoList[];
		selfDao:PlayerDaoList;
	}
	export interface SC_CMD_SHOWCARD{
		cmd:number;
		body:SC_CMD_SHOWCARD_body;
	}
	export interface DaoRes{
		cardList:number[];
		iScore:number;
		cardType:number;
	}
	export interface PlayerCompareRes{
		chairId:number;
		resList:DaoRes[];
		iTotalScore:number;
		daqiangList:number[];
		hongbolang:boolean;
		bIsMinPai:boolean;
	}
	export interface SC_CMD_COMPARE_body{
		compareSeq:PlayerCompareRes[];
	}
	export interface SC_CMD_COMPARE{
		cmd:number;
		body:SC_CMD_COMPARE_body;
	}
	export interface SC_CMD_MATCH_CARDS_body{
		firstList:number[];
		middleList:number[];
		lastList:number[];
	}
	export interface SC_CMD_MATCH_CARDS{
		cmd:number;
		body:SC_CMD_MATCH_CARDS_body;
	}
	export interface CS_CMD_ONE_KEY_BAIPAI{
		cmd:number;
	}
	export interface SC_CMD_ONE_KEY_BAIPAI_body{
		firstList:number[];
		middleList:number[];
		lastList:number[];
	}
	export interface SC_CMD_ONE_KEY_BAIPAI{
		cmd:number;
		body:SC_CMD_ONE_KEY_BAIPAI_body;
	}
	export interface CS_CMD_CHECK_BAIPAI_body{
		firstList:number[];
		middleList:number[];
		lastList:number[];
		curDao:number;
	}
	export interface CS_CMD_CHECK_BAIPAI{
		cmd:number;
		body:CS_CMD_CHECK_BAIPAI_body;
	}
	export interface SC_CMD_CHECK_BAIPAI_body{
		firstList:number[];
		middleList:number[];
		lastList:number[];
		bIsDaoShui:boolean;
		filterCardList:FilterCardMsg[];
		curDao:number;
	}
	export interface SC_CMD_CHECK_BAIPAI{
		cmd:number;
		body:SC_CMD_CHECK_BAIPAI_body;
	}
	export interface CS_CMD_QUERY_NOTICE{
		cmd:number;
	}
	export interface SC_CMD_QUERY_NOTICE_body{
		filterCardList:FilterCardMsg[];
	}
	export interface SC_CMD_QUERY_NOTICE{
		cmd:number;
		body:SC_CMD_QUERY_NOTICE_body;
	}
	export interface PlayerGameInfo{
		chairId:number;
		winCount:number;
		loseCount:number;
		peaceCount:number;
		totalScore:number;
	}
	export interface SC_CMD_GAME_OVER_body{
		playerGameResList:PlayerGameInfo[];
	}
	export interface SC_CMD_GAME_OVER{
		cmd:number;
		body:SC_CMD_GAME_OVER_body;
	}

}