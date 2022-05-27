// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NavcoinSDKGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NAVCOINSDK_API UNavcoinSDKGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UNavcoinSDKGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init();
	UFUNCTION (BlueprintCallable)
	void ShowWidget();
private:
	TSubclassOf<class UUserWidget> MainMenuWidgetClass;
};
