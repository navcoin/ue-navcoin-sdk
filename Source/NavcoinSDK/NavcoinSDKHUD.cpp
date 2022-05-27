// Fill out your copyright notice in the Description page of Project Settings.


#include "NavcoinSDKHUD.h"

void ANavcoinSDKHUD::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT("HUD"));
}