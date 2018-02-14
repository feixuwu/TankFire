#include "MessageProto.h"
#include "Engine.h"
#include "Kismet/BlueprintFunctionLibrary.h"


int UMessageProtocommandBlueprintLibrary::CMD_CLIENT_REQUEST_QUEUE(){
	return 1;
}

int UMessageProtocommandBlueprintLibrary::CMD_CLIENT_JOIN_GAME(){
	return 2;
}

int UMessageProtocommandBlueprintLibrary::CMD_CLIENT_EMOTION(){
	return 3;
}

int UMessageProtocommandBlueprintLibrary::CMD_CLIENT_CANCEL_QUEUE(){
	return 16;
}

int UMessageProtocommandBlueprintLibrary::CMD_CLIENT_QUERYZONE(){
	return 17;
}

int UMessageProtocommandBlueprintLibrary::CMD_CLIENT_QUERYACCOUNT(){
	return 18;
}

int UMessageProtocommandBlueprintLibrary::CMD_GS_FETCH_USERTOKEN(){
	return 4;
}

int UMessageProtocommandBlueprintLibrary::CMD_GS_ADD_USER(){
	return 5;
}

int UMessageProtocommandBlueprintLibrary::CMD_GS_QUERYACCOUNT(){
	return 101;
}

int UMessageProtocommandBlueprintLibrary::CMD_GS_UPDATEACCOUNT(){
	return 102;
}

int UMessageProtocommandBlueprintLibrary::CMD_GS_CLOSE(){
	return 103;
}

int UMessageProtoenResultBlueprintLibrary::enResult_OK(){
	return 0;
}

int UMessageProtoenResultBlueprintLibrary::enResult_Fail(){
	return 1;
}

UCS_CMD_GS_CLOSE::UCS_CMD_GS_CLOSE(){
}

UCS_CMD_CLIENT_QUERYACCOUNT::UCS_CMD_CLIENT_QUERYACCOUNT(){
}

UAccountData::UAccountData(){
}

UCS_CMD_GS_UPDATEACCOUNT::UCS_CMD_GS_UPDATEACCOUNT(){
	accountData = CreateDefaultSubobject<UAccountData>(TEXT("accountData"));
}

UCS_CMD_GS_QUERYACCOUNT::UCS_CMD_GS_QUERYACCOUNT(){
}

USC_CMD_GS_QUERYACCOUNT::USC_CMD_GS_QUERYACCOUNT(){
	accountData = CreateDefaultSubobject<UAccountData>(TEXT("accountData"));
}

USC_CMD_CLIENT_QUERYACCOUNT::USC_CMD_CLIENT_QUERYACCOUNT(){
	accountData = CreateDefaultSubobject<UAccountData>(TEXT("accountData"));
}

UServerZone::UServerZone(){
}

USC_CMD_CLIENT_QUERYZONE::USC_CMD_CLIENT_QUERYZONE(){
}

UCS_CMD_CLIENT_QUERYZONE::UCS_CMD_CLIENT_QUERYZONE(){
}

UCS_CMD_CLIENT_CANCEL_QUEUE::UCS_CMD_CLIENT_CANCEL_QUEUE(){
}

USC_CMD_CLIENT_CANCEL_QUEUE::USC_CMD_CLIENT_CANCEL_QUEUE(){
}

UUserInfo::UUserInfo(){
}

UUserTokenInfo::UUserTokenInfo(){
}

USC_CMD_GS_ADD_USER::USC_CMD_GS_ADD_USER(){
	newUser = CreateDefaultSubobject<UUserTokenInfo>(TEXT("newUser"));
}

UCS_CMD_GS_FETCH_USERTOKEN::UCS_CMD_GS_FETCH_USERTOKEN(){
}

USC_CMD_GS_FETCH_USERTOKEN::USC_CMD_GS_FETCH_USERTOKEN(){
}

UCS_CMD_CLIENT_REQUEST_QUEUE::UCS_CMD_CLIENT_REQUEST_QUEUE(){
	userInfo = CreateDefaultSubobject<UUserInfo>(TEXT("userInfo"));
}

USC_CMD_CLIENT_REQUEST_QUEUE::USC_CMD_CLIENT_REQUEST_QUEUE(){
}

USC_CMD_CLIENT_JOIN_GAME::USC_CMD_CLIENT_JOIN_GAME(){
}

UCS_CMD_CLIENT_EMOTION::UCS_CMD_CLIENT_EMOTION(){
}

USC_CMD_CLIENT_EMOTION::USC_CMD_CLIENT_EMOTION(){
}

