#pragma once
#include "Engine.h"
#include "MessageProto.generated.h"
UCLASS()
class  UMessageProtocommandBlueprintLibrary : public UBlueprintFunctionLibrary{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "MessageProto")
	static int CMD_CLIENT_REQUEST_QUEUE();
	UFUNCTION(BlueprintPure, Category = "MessageProto")
	static int CMD_CLIENT_JOIN_GAME();
	UFUNCTION(BlueprintPure, Category = "MessageProto")
	static int CMD_CLIENT_EMOTION();
	UFUNCTION(BlueprintPure, Category = "MessageProto")
	static int CMD_CLIENT_CANCEL_QUEUE();
	UFUNCTION(BlueprintPure, Category = "MessageProto")
	static int CMD_CLIENT_QUERYZONE();
	UFUNCTION(BlueprintPure, Category = "MessageProto")
	static int CMD_CLIENT_QUERYACCOUNT();
	UFUNCTION(BlueprintPure, Category = "MessageProto")
	static int CMD_GS_FETCH_USERTOKEN();
	UFUNCTION(BlueprintPure, Category = "MessageProto")
	static int CMD_GS_ADD_USER();
	UFUNCTION(BlueprintPure, Category = "MessageProto")
	static int CMD_GS_QUERYACCOUNT();
	UFUNCTION(BlueprintPure, Category = "MessageProto")
	static int CMD_GS_UPDATEACCOUNT();
	UFUNCTION(BlueprintPure, Category = "MessageProto")
	static int CMD_GS_CLOSE();
};

UCLASS()
class  UMessageProtoenResultBlueprintLibrary : public UBlueprintFunctionLibrary{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "MessageProto")
	static int enResult_OK();
	UFUNCTION(BlueprintPure, Category = "MessageProto")
	static int enResult_Fail();
};

UCLASS(BlueprintType, Blueprintable)
class UCS_CMD_GS_CLOSE:public UObject {
GENERATED_BODY()
public:
	UCS_CMD_GS_CLOSE();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
};

UCLASS(BlueprintType, Blueprintable)
class UCS_CMD_CLIENT_QUERYACCOUNT:public UObject {
GENERATED_BODY()
public:
	UCS_CMD_CLIENT_QUERYACCOUNT();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString account;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString name;
};

UCLASS(BlueprintType, Blueprintable)
class UAccountData:public UObject {
GENERATED_BODY()
public:
	UAccountData();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString account;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int segment;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int star;
};

UCLASS(BlueprintType, Blueprintable)
class UCS_CMD_GS_UPDATEACCOUNT:public UObject {
GENERATED_BODY()
public:
	UCS_CMD_GS_UPDATEACCOUNT();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	UAccountData* accountData;
};

UCLASS(BlueprintType, Blueprintable)
class UCS_CMD_GS_QUERYACCOUNT:public UObject {
GENERATED_BODY()
public:
	UCS_CMD_GS_QUERYACCOUNT();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString accout;
};

UCLASS(BlueprintType, Blueprintable)
class USC_CMD_GS_QUERYACCOUNT:public UObject {
GENERATED_BODY()
public:
	USC_CMD_GS_QUERYACCOUNT();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int result;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	UAccountData* accountData;
};

UCLASS(BlueprintType, Blueprintable)
class USC_CMD_CLIENT_QUERYACCOUNT:public UObject {
GENERATED_BODY()
public:
	USC_CMD_CLIENT_QUERYACCOUNT();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	UAccountData* accountData;
};

UCLASS(BlueprintType, Blueprintable)
class UServerZone:public UObject {
GENERATED_BODY()
public:
	UServerZone();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString sampleIp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int sampleport;
};

UCLASS(BlueprintType, Blueprintable)
class USC_CMD_CLIENT_QUERYZONE:public UObject {
GENERATED_BODY()
public:
	USC_CMD_CLIENT_QUERYZONE();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	TArray<UServerZone*> zoneList;
};

UCLASS(BlueprintType, Blueprintable)
class UCS_CMD_CLIENT_QUERYZONE:public UObject {
GENERATED_BODY()
public:
	UCS_CMD_CLIENT_QUERYZONE();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
};

UCLASS(BlueprintType, Blueprintable)
class UCS_CMD_CLIENT_CANCEL_QUEUE:public UObject {
GENERATED_BODY()
public:
	UCS_CMD_CLIENT_CANCEL_QUEUE();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
};

UCLASS(BlueprintType, Blueprintable)
class USC_CMD_CLIENT_CANCEL_QUEUE:public UObject {
GENERATED_BODY()
public:
	USC_CMD_CLIENT_CANCEL_QUEUE();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	bool result;
};

UCLASS(BlueprintType, Blueprintable)
class UUserInfo:public UObject {
GENERATED_BODY()
public:
	UUserInfo();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString account;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString headurl;
};

UCLASS(BlueprintType, Blueprintable)
class UUserTokenInfo:public UObject {
GENERATED_BODY()
public:
	UUserTokenInfo();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString account;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString headurl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString token;
};

UCLASS(BlueprintType, Blueprintable)
class USC_CMD_GS_ADD_USER:public UObject {
GENERATED_BODY()
public:
	USC_CMD_GS_ADD_USER();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	UUserTokenInfo* newUser;
};

UCLASS(BlueprintType, Blueprintable)
class UCS_CMD_GS_FETCH_USERTOKEN:public UObject {
GENERATED_BODY()
public:
	UCS_CMD_GS_FETCH_USERTOKEN();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString serverKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString host;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int port;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int zone;
};

UCLASS(BlueprintType, Blueprintable)
class USC_CMD_GS_FETCH_USERTOKEN:public UObject {
GENERATED_BODY()
public:
	USC_CMD_GS_FETCH_USERTOKEN();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int result;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	TArray<UUserTokenInfo*> userList;
};

UCLASS(BlueprintType, Blueprintable)
class UCS_CMD_CLIENT_REQUEST_QUEUE:public UObject {
GENERATED_BODY()
public:
	UCS_CMD_CLIENT_REQUEST_QUEUE();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	UUserInfo* userInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int zoneId;
};

UCLASS(BlueprintType, Blueprintable)
class USC_CMD_CLIENT_REQUEST_QUEUE:public UObject {
GENERATED_BODY()
public:
	USC_CMD_CLIENT_REQUEST_QUEUE();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int result;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString token;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int zoneId;
};

UCLASS(BlueprintType, Blueprintable)
class USC_CMD_CLIENT_JOIN_GAME:public UObject {
GENERATED_BODY()
public:
	USC_CMD_CLIENT_JOIN_GAME();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString host;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int port;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString serverkey;
};

UCLASS(BlueprintType, Blueprintable)
class UCS_CMD_CLIENT_EMOTION:public UObject {
GENERATED_BODY()
public:
	UCS_CMD_CLIENT_EMOTION();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString serverKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int emotion;
};

UCLASS(BlueprintType, Blueprintable)
class USC_CMD_CLIENT_EMOTION:public UObject {
GENERATED_BODY()
public:
	USC_CMD_CLIENT_EMOTION();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int cmd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	FString account;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = MessageProto)
	int emotion;
};

