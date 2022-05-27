// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NavcoinSDKGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class NAVCOINSDK_API ANavcoinSDKGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Class Types")
		TSubclassOf<UUserWidget> WidgetClass;
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		class UHomeWidget* HomeWidget;
	virtual void BeginPlay() override;
public:
	static FString GetProjectID();
};
