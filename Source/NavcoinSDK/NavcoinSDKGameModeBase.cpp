// Fill out your copyright notice in the Description page of Project Settings.


#include "NavcoinSDKGameModeBase.h"

#include "HomeWidget.h"
#include "Blueprint/UserWidget.h"
void ANavcoinSDKGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("fullscreen");
	FString Code = "";
	FString ConfigFile = FPaths::ProjectConfigDir();
	ConfigFile.Append(TEXT("config.txt"));
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	if (FileManager.FileExists(*ConfigFile))
	{
		if (FFileHelper::LoadFileToString(Code, *ConfigFile, FFileHelper::EHashOptions::None))
		{
			UE_LOG(LogTemp, Warning, TEXT("Code from file -> %s"), *Code);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Did not load code from file"));
		}
	}
	else
	{
		FString CharacterSet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		uint32 AmountOfCharacters=8;
		Code.AppendInt(FDateTime::Now().ToUnixTimestamp());
		Code.Append("-");
		for (uint32 i = 0; i < AmountOfCharacters; ++i)
		{
			Code.Append(CharacterSet.Mid(FMath::RandRange(0, CharacterSet.Len()), 1));
		}
		UE_LOG(LogTemp, Warning, TEXT("ERROR: Can not read the file because it was not found."));
		UE_LOG(LogTemp, Warning, TEXT("Expected file location: %s"), *ConfigFile);
		if (FFileHelper::SaveStringToFile(Code, *ConfigFile))
		{
			UE_LOG(LogTemp, Warning, TEXT("Code saved \"%s\" to the text file"), *Code);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to write code to file."));
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, Code);
	//GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT("BEGIN PLAY"));
	if (IsValid(WidgetClass))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT("WIDGET VALID"));
		HomeWidget = Cast<UHomeWidget>(CreateWidget(GetWorld(), WidgetClass));
		if (HomeWidget!=nullptr)
		{
			HomeWidget->AddToViewport();
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(HomeWidget->TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->bShowMouseCursor = true;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT("NOT VALID"));
	}
}

FString ANavcoinSDKGameModeBase::GetProjectID()
{
	FString ProjectID="1";
	return ProjectID;
}