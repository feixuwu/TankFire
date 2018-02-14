// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBlueprintLibrary.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/Engine.h"
#include "SceneView.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/LocalPlayer.h"
#include "EZServerGameMode.h"
#include "EZOnlineGameInstance.h"


static void BuildProjectionMatrix(FIntPoint RenderTargetSize, ECameraProjectionMode::Type ProjectionType, float FOV, float InOrthoWidth, FMatrix& ProjectionMatrix)
{
	float XAxisMultiplier;
	float YAxisMultiplier;

	if (RenderTargetSize.X > RenderTargetSize.Y)
	{
		// if the viewport is wider than it is tall
		XAxisMultiplier = 1.0f;
		YAxisMultiplier = RenderTargetSize.X / (float)RenderTargetSize.Y;
	}
	else
	{
		// if the viewport is taller than it is wide
		XAxisMultiplier = RenderTargetSize.Y / (float)RenderTargetSize.X;
		YAxisMultiplier = 1.0f;
	}

	if (ProjectionType == ECameraProjectionMode::Orthographic)
	{
		check((int32)ERHIZBuffer::IsInverted);
		const float OrthoWidth = InOrthoWidth / 2.0f;
		const float OrthoHeight = InOrthoWidth / 2.0f * XAxisMultiplier / YAxisMultiplier;

		const float NearPlane = 0;
		const float FarPlane = WORLD_MAX / 8.0f;

		const float ZScale = 1.0f / (FarPlane - NearPlane);
		const float ZOffset = -NearPlane;

		ProjectionMatrix = FReversedZOrthoMatrix(
			OrthoWidth,
			OrthoHeight,
			ZScale,
			ZOffset
		);
	}
	else
	{
		if ((int32)ERHIZBuffer::IsInverted)
		{
			ProjectionMatrix = FReversedZPerspectiveMatrix(
				FOV,
				FOV,
				XAxisMultiplier,
				YAxisMultiplier,
				GNearClippingPlane,
				GNearClippingPlane
			);
		}
		else
		{
			ProjectionMatrix = FPerspectiveMatrix(
				FOV,
				FOV,
				XAxisMultiplier,
				YAxisMultiplier,
				GNearClippingPlane,
				GNearClippingPlane
			);
		}
	}
}

bool UTankBlueprintLibrary::ProjectSceneCapturePosition(USceneCaptureComponent2D* sceneCapture, const FVector& worldPosition, FVector2D& screenPo)
{
	if (sceneCapture == nullptr)
	{
		return false;
	}

	if (sceneCapture->TextureTarget == nullptr)
	{
		return false;
	}

	FTransform Transform = sceneCapture->GetComponentToWorld();
	FVector ViewLocation = Transform.GetTranslation();

	Transform.SetTranslation(FVector::ZeroVector);
	Transform.SetScale3D(FVector::OneVector);
	FMatrix ViewRotationMatrix = Transform.ToInverseMatrixWithScale();

	// swap axis st. x=z,y=x,z=y (unreal coord space) so that z is up
	ViewRotationMatrix = ViewRotationMatrix * FMatrix(
		FPlane(0, 0, 1, 0),
		FPlane(1, 0, 0, 0),
		FPlane(0, 1, 0, 0),
		FPlane(0, 0, 0, 1));
	const float FOV = sceneCapture->FOVAngle * (float)PI / 360.0f;
	FIntPoint CaptureSize(sceneCapture->TextureTarget->GetSurfaceWidth(), sceneCapture->TextureTarget->GetSurfaceHeight());

	FMatrix ProjectionMatrix;
	if (sceneCapture->bUseCustomProjectionMatrix)
	{
		ProjectionMatrix = sceneCapture->CustomProjectionMatrix;
	}
	else
	{
		BuildProjectionMatrix(CaptureSize, sceneCapture->ProjectionType, FOV, sceneCapture->OrthoWidth, ProjectionMatrix);
	}

	FVector ViewOrigin = sceneCapture->GetAttachmentRoot()->GetComponentLocation();
	FMatrix const ViewProjectionMatrix = FTranslationMatrix(-ViewOrigin) * ViewRotationMatrix * ProjectionMatrix;

	FIntRect constraintView(0, 0, CaptureSize.X, CaptureSize.Y);

	const bool bResult = FSceneView::ProjectWorldToScreen(worldPosition, constraintView, ViewProjectionMatrix, screenPo);

	return bResult;
}

TArray<APlayerState*> UTankBlueprintLibrary::SortPlayerState(const TArray<APlayerState*>& OrgArray)
{
	TArray<APlayerState*> PlayerStateArray = OrgArray;
	PlayerStateArray.Sort([](const APlayerState& first, const APlayerState& second) {
		const ATankPlayerState* firstTankState = Cast<ATankPlayerState>(&first);
		const ATankPlayerState* secondTankState = Cast<ATankPlayerState>(&second);

		int firstScore = firstTankState->KillCount - firstTankState->DeathCount;
		int secondScore = secondTankState->KillCount - secondTankState->DeathCount;

		if (firstScore != secondScore)
		{
			return firstScore > secondScore;
		}

		return firstTankState->UniqueId.ToString() > secondTankState->UniqueId.ToString();
	});

	return PlayerStateArray;
}

int UTankBlueprintLibrary::CalcStarCount(UDataTable* DataTable, UAccountData* AccountData)
{
	if (AccountData == nullptr)
	{
		return 0;
	}

	int iRet = 0;
	for (int i = 0; i <= AccountData->segment; i++)
	{
		FName rowName = UKismetStringLibrary::Conv_StringToName(UKismetStringLibrary::Conv_IntToString(i));
		FSegmentConfig* pSegmentConfig = DataTable->FindRow<FSegmentConfig>(rowName, TEXT("CalcStar") );
		if (pSegmentConfig == nullptr)
		{
			continue;
		}

		if (i < AccountData->segment)
		{
			iRet += pSegmentConfig->StartCnt + 1;
		}
		else
		{
			iRet += AccountData->star;
		}
	}

	return iRet;
}

void UTankBlueprintLibrary::CalcLocalPlayerResult(UObject* WorldContextObjec, UDataTable* DataTable, int& cup, int& starStatus, int& newSegment, int& newStar)
{
	cup = 0;
	starStatus = 0;
	
	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(WorldContextObjec, 0);
	if (!pPlayerController)
	{
		return;
	}

	ATankPlayerState* pTankPlayerState = Cast<ATankPlayerState>(pPlayerController->PlayerState);
	if (!pTankPlayerState)
	{
		return;
	}

	AGameStateBase* pGameStateBase = UGameplayStatics::GetGameState(WorldContextObjec);
	if (pGameStateBase == nullptr)
	{
		return;
	}

	TArray<APlayerState*> sortedPlayerState = SortPlayerState(pGameStateBase->PlayerArray);
	
	int iRank = 0;
	if (!sortedPlayerState.Find(pTankPlayerState, iRank))
	{
		return;
	}

	iRank++;

	UEZOnlineGameInstance* pGameInstance = Cast<UEZOnlineGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObjec) );
	if (pGameInstance == nullptr || pGameInstance->mAccountSaveGame == nullptr)
	{
		return;
	}

	// check star get or lost
	FName rowName = UKismetStringLibrary::Conv_StringToName(UKismetStringLibrary::Conv_IntToString(pGameInstance->mAccountSaveGame->Segment));
	FSegmentConfig* pSegmentConfig = DataTable->FindRow<FSegmentConfig>(rowName, TEXT("GameResult"));

	if (pSegmentConfig == nullptr)
	{
		return;
	}

	newSegment = pGameInstance->mAccountSaveGame->Segment;
	newStar = pGameInstance->mAccountSaveGame->Star;

	if (pTankPlayerState->KillCount > pTankPlayerState->DeathCount)
	{
		cup += pTankPlayerState->KillCount - pTankPlayerState->DeathCount;
	}

	if (pGameStateBase->PlayerArray.Num() < pSegmentConfig->GetStarMinPlayerCount)
	{
		return;
	}
	
	if (iRank <= pSegmentConfig->GetStarMaxRank)
	{
		starStatus = 1;
		if (pGameInstance->mAccountSaveGame->Star >= pSegmentConfig->StartCnt)
		{
			FName nextRowName = UKismetStringLibrary::Conv_StringToName(UKismetStringLibrary::Conv_IntToString(pGameInstance->mAccountSaveGame->Segment + 1));
			FSegmentConfig* pNextSegmentConfig = DataTable->FindRow<FSegmentConfig>(nextRowName, TEXT("NextGameResult"));
			if (!pNextSegmentConfig)
			{
				starStatus = 0;
			}
			else
			{
				newSegment = pGameInstance->mAccountSaveGame->Segment + 1;
				newStar = 0;
			}
		}
		else
		{
			newStar = pGameInstance->mAccountSaveGame->Star + 1;
		}
	}

	if (iRank >= pSegmentConfig->LostStarMinRank)
	{
		starStatus = -1;

		if (pGameInstance->mAccountSaveGame->Star > 0)
		{
			newStar = pGameInstance->mAccountSaveGame->Star - 1;
		}
		else
		{
			if (pGameInstance->mAccountSaveGame->Segment > 0)
			{
				FName preRowName = UKismetStringLibrary::Conv_StringToName(UKismetStringLibrary::Conv_IntToString(pGameInstance->mAccountSaveGame->Segment - 1));
				FSegmentConfig* pPreSegmentConfig = DataTable->FindRow<FSegmentConfig>(preRowName, TEXT("PreGameResult"));
				if (pPreSegmentConfig)
				{
					newSegment = pGameInstance->mAccountSaveGame->Segment - 1;
					newStar = pPreSegmentConfig->StartCnt;
				}
			}
			else
			{
				starStatus = 0;
			}
		}
	}
}

void UTankBlueprintLibrary::ProcessGameResult(UObject* WorldContextObjec, UDataTable* DataTable)
{
	// sort player state
	AGameStateBase* pGameStateBase = UGameplayStatics::GetGameState(WorldContextObjec);
	if (pGameStateBase == nullptr)
	{
		return;
	}

	AEZServerGameMode* pGameMode = Cast<AEZServerGameMode>(UGameplayStatics::GetGameMode(WorldContextObjec) );
	if (pGameMode == nullptr)
	{
		return;
	}

	TArray<APlayerState*> sortedPlayerState = SortPlayerState(pGameStateBase->PlayerArray);
	for (int i = 0; i < sortedPlayerState.Num(); i++)
	{
		int iRank = i + 1;
		
		ATankPlayerState* pTankPlayerState = Cast<ATankPlayerState>(sortedPlayerState[i]);
		if (!pTankPlayerState)
		{
			continue;
		}

		if (!pGameMode->mUserAccountList.Contains(pTankPlayerState->UniqueId.ToString()))
		{
			continue;
		}

		UAccountData* accountData = pGameMode->mUserAccountList.FindRef(pTankPlayerState->UniqueId.ToString());

		// get cup
		if (pTankPlayerState->KillCount > pTankPlayerState->DeathCount)
		{
			accountData->cup += pTankPlayerState->KillCount - pTankPlayerState->DeathCount;
		}

		// check add or sub star
		FName rowName = UKismetStringLibrary::Conv_StringToName(UKismetStringLibrary::Conv_IntToString(accountData->segment) );
		FSegmentConfig* pSegmentConfig = DataTable->FindRow<FSegmentConfig>(rowName, TEXT("GameResult") );

		if (pSegmentConfig == nullptr)
		{
			continue;
		}

		if (pGameStateBase->PlayerArray.Num() >= pSegmentConfig->GetStarMinPlayerCount)
		{
			// add star?
			if (iRank <= pSegmentConfig->GetStarMaxRank)
			{
				accountData->star++;
				if (accountData->star > pSegmentConfig->StartCnt)
				{
					FName nextRowName = UKismetStringLibrary::Conv_StringToName(UKismetStringLibrary::Conv_IntToString(accountData->segment + 1));
					FSegmentConfig* pNextSegmentConfig = DataTable->FindRow<FSegmentConfig>(nextRowName, TEXT("NextGameResult"));
					if (!pNextSegmentConfig)
					{
						accountData->star--;
					}
					else
					{
						accountData->segment++;
						accountData->star = 0;
					}
				}
			}

			// lost star?
			if (iRank >= pSegmentConfig->LostStarMinRank)
			{
				if (accountData->star > 0)
				{
					accountData->star--;
				}
				else
				{
					if (accountData->segment > 0)
					{
						FName preRowName = UKismetStringLibrary::Conv_StringToName(UKismetStringLibrary::Conv_IntToString(accountData->segment - 1));
						FSegmentConfig* pPreSegmentConfig = DataTable->FindRow<FSegmentConfig>(preRowName, TEXT("PreGameResult"));
						if (pPreSegmentConfig)
						{
							accountData->segment--;
							accountData->star = pPreSegmentConfig->StartCnt;
						}
					}
				}
			}
		}

		// update data
		pGameMode->UpdateUserAccount(accountData);
	}
}

/*FString UTankBlueprintLibrary::GetNickName(UObject* WorldContextObjec)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObjec);
	if (World == nullptr)
	{
		return TEXT("");
	}

	ULocalPlayer* pLocalPlayer = World->GetFirstLocalPlayerFromController();
	if (pLocalPlayer == nullptr)
	{
		return TEXT("");
	}

	return pLocalPlayer->GetNickname();
}*/

void UTankBlueprintLibrary::FinishGame(UObject* WorldContextObjec)
{
	if (!UKismetSystemLibrary::IsServer(WorldContextObjec) )
	{
		return;
	}

	// notify game finish
	AEZServerGameMode* pGameMode = Cast<AEZServerGameMode>(UGameplayStatics::GetGameMode(WorldContextObjec));
	if (pGameMode == nullptr)
	{
		return;
	}

	pGameMode->SendCenterClose();

	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObjec);
	if (World == nullptr)
	{
		return;
	}

	AGameMode* GameMode = Cast<AGameMode>(World->GetAuthGameMode() );
	if (GameMode != nullptr)
	{
		GameMode->EndMatch();
	}

	for (FConstControllerIterator It = World->GetControllerIterator(); It; ++It)
	{
		(*It)->GameHasEnded(NULL, false);
	}
	
	for (FConstPawnIterator It = World->GetPawnIterator(); It; ++It)
	{
		(*It)->TurnOff();
	}
}
