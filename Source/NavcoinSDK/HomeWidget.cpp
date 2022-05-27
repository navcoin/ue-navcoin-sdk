// Fill out your copyright notice in the Description page of Project Settings.


#include "HomeWidget.h"

#include "NavcoinSDKGameModeBase.h"

void UHomeWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (TTitle!=nullptr)
	{
		TTitle->SetText(FText::Format(NSLOCTEXT("MainMenu", "text1", "Unreal Engine Navcoin SDK Sample {0}"), 1));
	}
}

void UHomeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("Native construct"));
	FString file = FPaths::ProjectConfigDir();
	FString QRCode;
	FString Code;
	FString URL = "http://priverse.org/api/qr/?code=";
	QRCode.Append(ANavcoinSDKGameModeBase::GetProjectID());
	QRCode.Append(":");
	file.Append(TEXT("config.txt"));
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	if (FileManager.FileExists(*file))
	{
		if (FFileHelper::LoadFileToString(Code, *file, FFileHelper::EHashOptions::None))
		{
			UE_LOG(LogTemp, Warning, TEXT("Code -> %s"), *Code);
			QRCode.Append(Code);
			UE_LOG(LogTemp, Warning, TEXT("QR Code -> %s"), *QRCode);
			URL.Append(QRCode);
			UE_LOG(LogTemp, Warning, TEXT("QR Code URL -> %s"), *URL);
			WebBrowser1->LoadURL(URL);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Did not load code from file"));
		}
	}
	if (ButtonLevel1)
	{
		ButtonLevel1->OnClicked.AddDynamic(this, &UHomeWidget::OnButtonLevel1);
	}
	if (ButtonLevel2)
	{
		ButtonLevel2->OnClicked.AddDynamic(this, &UHomeWidget::OnButtonLevel2);
	}
	if (ButtonQuit)
	{
		ButtonQuit->OnClicked.AddDynamic(this, &UHomeWidget::OnButtonQuit);
	}
	/*
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([&]
		{
			UE_LOG(LogTemp, Warning, TEXT("This text will appear in the console 10 seconds after execution"))
		});
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 10, false);
	*/
}

void UHomeWidget::OnButtonQuit()
{
	UE_LOG(LogTemp, Warning, TEXT("On button quit!"));
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

void UHomeWidget::OnButtonLevel1()
{
	UE_LOG(LogTemp, Warning, TEXT("On button level-1!"));
	//GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT("Level-1"));
	UGameplayStatics::OpenLevel(GetWorld(), "FirstPersonMap");
}

void UHomeWidget::OnButtonLevel2()
{
	UE_LOG(LogTemp, Warning, TEXT("On button level-1!"));
	//GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT("Level-2"));
	UGameplayStatics::OpenLevel(GetWorld(), "FirstPersonMap2");
}