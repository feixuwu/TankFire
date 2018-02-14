var MessageProto = {
    command:{
        enum:1,
        
        // 客户端和CenterServer消息
        CMD_CLIENT_REQUEST_QUEUE:1,      // 排队
        CMD_CLIENT_JOIN_GAME:2,          // 加入游戏
        CMD_CLIENT_EMOTION:3,            // 表情
		CMD_CLIENT_CANCEL_QUEUE:16,		 // 取消排队
        CMD_CLIENT_QUERYZONE:17,         // 查询区
        CMD_CLIENT_QUERYACCOUNT:18,      // query account data

        // 服务器和CenterServer消息
        CMD_GS_FETCH_USERTOKEN:4,         // 游戏服创建成功后，从CenterServer拉取UserToken, 如果拉取失败，游戏服可以反复重试。
        CMD_GS_ADD_USER:5,                // Center通知GS新增一个玩家
        CMD_GS_QUERYACCOUNT:101,          
        CMD_GS_UPDATEACCOUNT:102,
        CMD_GS_CLOSE:103,               // 关闭GS        
    },

    CS_CMD_GS_CLOSE:{
        cmd:"int"
    },

    CS_CMD_CLIENT_QUERYACCOUNT:{
        cmd:"int",
        account:"string",
        name:"string",
    },

    AccountData:{
        account:"string",
        name:"string",
        cup:"int",
        segment:"int",
        star:"int",
    },

    CS_CMD_GS_UPDATEACCOUNT:{
        cmd:"int",
        accountData:"AccountData",
    },

    CS_CMD_GS_QUERYACCOUNT:{
        cmd:"int",
        accout:"string",
    },

    SC_CMD_GS_QUERYACCOUNT:{
        cmd:"int",
        result:"int",
        accountData:"AccountData",
    },

    SC_CMD_CLIENT_QUERYACCOUNT:{
        cmd:"int",
        accountData:"AccountData",
    },

    ServerZone:{
        Id:"int",
        name:"string",
        sampleIp:"string",              // this is not the game server ip, just a test ip for the client ping
        sampleport:"int",               // for test ping
    },

    SC_CMD_CLIENT_QUERYZONE:{
        cmd:"int",
        zoneList:":ServerZone",
    },

    CS_CMD_CLIENT_QUERYZONE:{
        cmd:"int",
    },
	
	
	CS_CMD_CLIENT_CANCEL_QUEUE:{
        cmd:"int",
	},
	
	SC_CMD_CLIENT_CANCEL_QUEUE:{
		cmd:"int",
		result:"bool",
	},

    enResult:{
        enum:1,
        enResult_OK:0,
        enResult_Fail:1,
    },

    
    UserInfo:{
        account:"string",
        name:"string",
        headurl:"string",
    },

    
    UserTokenInfo:{
        account:"string",
        name:"string",
        headurl:"string",
        token:"string",
    },

    SC_CMD_GS_ADD_USER:{
        cmd:"int",
        newUser:"UserTokenInfo",
    },


    CS_CMD_GS_FETCH_USERTOKEN:{
        cmd:"int",
        serverKey:"string",
        host:"string",
        port:"int",
        zone:"int",
    },



    SC_CMD_GS_FETCH_USERTOKEN:{
        cmd:"int",
        result:"int",
        userList:":UserTokenInfo",
    },


    CS_CMD_CLIENT_REQUEST_QUEUE:{
        cmd:"int",
        userInfo:"UserInfo",
        zoneId:"int",
    },

    SC_CMD_CLIENT_REQUEST_QUEUE:{
        cmd:"int",
        result:"int",
        token:"string",
        zoneId:"int",
    },

    SC_CMD_CLIENT_JOIN_GAME:{
        cmd:"int",
        host:"string",
        port:"int",
        serverkey:"string",
    },

    CS_CMD_CLIENT_EMOTION:{
        cmd:"int",
        serverKey:"string",
        emotion:"int",
    },

    SC_CMD_CLIENT_EMOTION:{
        cmd:"int",
        account:"string",
        emotion:"int",
    },

}

global.MessageProto = MessageProto
exports.MessageProto = MessageProto