// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "GameFramework/GameModeBase.h"
#include "NavcoinSDKGameMode.generated.h"

UCLASS(minimalapi)
class ANavcoinSDKGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANavcoinSDKGameMode();
	virtual void StartPlay() override;
private:
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
};