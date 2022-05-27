// Fill out your copyright notice in the Description page of Project Settings.


#include "NavcoinSDKGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
UNavcoinSDKGameInstance::UNavcoinSDKGameInstance(const FObjectInitializer& ObjectInitializer)
{
	/*
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT("UNavcoinSDKGameInstance"));
	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidget(TEXT("/Game/MainMenu"));
	if (!ensure(MainMenuWidget.Class != nullptr))
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT("NOT FOUND"));
		return;
	}
	MainMenuWidgetClass = MainMenuWidget.Class;
	*/
}

void UNavcoinSDKGameInstance::Init()
{
	/*
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT("INIT"));
	UE_LOG(LogTemp, Warning, TEXT("Found -> %s"), *MainMenuWidgetClass->GetName());
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, *MainMenuWidgetClass->GetName());
	*/
}

void UNavcoinSDKGameInstance::ShowWidget()
{
	/*
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT("SHOW WIDGET"));
	UUserWidget* MainMenu = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
	MainMenu->AddToViewport();
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(MainMenu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
	*/
}
