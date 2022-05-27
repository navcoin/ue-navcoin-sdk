// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Runtime/UMG/Public/Components/TextBlock.h>
#include <Runtime/UMG/Public/Components/Button.h>
#include "Kismet/GameplayStatics.h"
#include "WebBrowser.h"
#include "HomeWidget.generated.h"

/**
 * 
 */
UCLASS()
class NAVCOINSDK_API UHomeWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* TTitle;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UWebBrowser* WebBrowser1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* ButtonQuit;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* ButtonLevel1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* ButtonLevel2;
	virtual void NativeOnInitialized() override;
	virtual	void NativeConstruct() override;
	UFUNCTION()
		void OnButtonLevel1();
	UFUNCTION()
		void OnButtonLevel2();
	UFUNCTION()
		void OnButtonQuit();
};
