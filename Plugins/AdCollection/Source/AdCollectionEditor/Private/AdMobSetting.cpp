// Fill out your copyright notice in the Description page of Project Settings.

#include "AdCollectionEditor.h"
#include "AdMobSetting.h"




#if WITH_EDITOR
void UAdMobSetting::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	SaveConfig(CPF_Config, *GetDefaultConfigFilename() );
}
#endif
