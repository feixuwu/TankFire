// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/SceneCaptureComponent2D.h"
#include "TankPlayerState.h"
#include "Engine/DataTable.h"
#include "MessageProto.h"
#include "TankBlueprintLibrary.generated.h"


USTRUCT(BlueprintType)
struct FSegmentConfig : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int SegmentID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText SegmentName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int StartCnt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int GetStarMinPlayerCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int GetStarMaxRank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int LostStarMinRank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* SegmentIcon;
};


/**
 * 
 */
UCLASS()
class TANKFIRE_API UTankBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Tank|BlueprintFunction")
	static bool ProjectSceneCapturePosition(USceneCaptureComponent2D* sceneCapture, const FVector& worldPosition, FVector2D& screenPos);

	UFUNCTION(BlueprintCallable, Category = "Tank|BlueprintFunction")
	static void FinishGame(UObject* WorldContextObjec);

	//UFUNCTION(BlueprintCallable, Category = "Tank|BlueprintFunction")
	//static FString GetNickName(UObject* WorldContextObjec);

	UFUNCTION(BlueprintCallable, Category = "Tank|BlueprintFunction")
	static TArray<APlayerState*> SortPlayerState(const TArray<APlayerState*>& PlayerStateArray);

	UFUNCTION(BlueprintCallable, Category = "Tank|BlueprintFunction")
	static void ProcessGameResult(UObject* WorldContextObjec, UDataTable* DataTable);

	UFUNCTION(BlueprintCallable, Category = "Tank|BlueprintFunction")
	static int CalcStarCount(UDataTable* DataTable, UAccountData* AccountData);
	
	UFUNCTION(BlueprintCallable, Category = "Tank|BlueprintFunction")
	static void CalcLocalPlayerResult(UObject* WorldContextObjec, UDataTable* DataTable, int& cup, int& starStatus, int& newSegment, int& newStar);
};
