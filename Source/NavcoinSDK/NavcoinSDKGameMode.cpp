// Copyright Epic Games, Inc. All Rights Reserved.

#include "NavcoinSDKGameMode.h"
#include "NavcoinSDKCharacter.h"
#include "NavcoinSDKGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
static TArray< TSharedPtr<FJsonValue> > GameItems;
static TArray< TSharedPtr<FJsonValue> > NFTs;
FString ApiURL = "https://api.nextwallet.org/testnet/CheckQR";
ANavcoinSDKGameMode::ANavcoinSDKGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void ANavcoinSDKGameMode::StartPlay()
{
	Super::StartPlay();
	FInputModeGameOnly InputModeData;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
	FString ConfigFile = FPaths::ProjectConfigDir();
	FString Code;
	ConfigFile.Append(TEXT("config.txt"));
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	if (FileManager.FileExists(*ConfigFile))
	{
		if (FFileHelper::LoadFileToString(Code, *ConfigFile, FFileHelper::EHashOptions::None))
		{
			UE_LOG(LogTemp, Warning, TEXT("Code -> %s"), *Code);
			GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT("Checking NFTs..."));
			UE_LOG(LogTemp, Display, TEXT("Checking NFTs with Code -> %s"), *Code);
			FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
			TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
			RequestObj->SetStringField("code", * Code);
			FString RequestBody;
			TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
			FJsonSerializer::Serialize(RequestObj, Writer);
			Request->OnProcessRequestComplete().BindUObject(this, &ANavcoinSDKGameMode::OnResponseReceived);
			Request->SetURL(ApiURL);
			Request->SetVerb("POST");
			Request->SetHeader("Content-Type", "application/json");
			Request->SetContentAsString(RequestBody);
			Request->ProcessRequest();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Did not load code from file"));
		}
	}
	GameItems.Empty();
	NFTs.Empty();
}

static bool IsNFTAvailable(FString NftFamilyID)
{
	bool bNFTExist = false;
	for (int32 index = 0; index < NFTs.Num(); index++)
	{
		TSharedPtr<FJsonObject> NFT = NFTs[index]->AsObject();
		if (*NFT->GetStringField("family_id") == NftFamilyID)
		{
			UE_LOG(LogTemp, Display, TEXT("Is nft available -> %s"), *NFT->GetStringField("family_id"));
			bNFTExist = true;
			return true;
			break;
		}
	}
	if (!bNFTExist) UE_LOG(LogTemp, Display, TEXT("NFT not found -> %s"), *NftFamilyID);

	return false;
}
static bool IsItemInInventory(FString ItemType, int32 ItemID)
{
	FString NftFamilyID;
	bool bItemFound = false;

	for (int32 index = 0; index < GameItems.Num(); index++)
	{
		TSharedPtr<FJsonObject> item = GameItems[index]->AsObject();
		int32 xItemID = item->GetIntegerField("ItemID");
		if (*item->GetStringField("ItemType") == ItemType && xItemID == ItemID)
		{
			NftFamilyID = *item->GetStringField("NftFamilyID");
			UE_LOG(LogTemp, Display, TEXT("Game item exist. NFT Family ID -> %s"), *NftFamilyID);
			bItemFound = true;
			break;
		}
	}
	if (bItemFound)
	{
		bool bNftFound = false;
		for (int32 index = 0; index < NFTs.Num(); index++)
		{
			TSharedPtr<FJsonObject> NFT = NFTs[index]->AsObject();
			if (*NFT->GetStringField("family_id") == NftFamilyID)
			{
				UE_LOG(LogTemp, Display, TEXT("NFT exist -> %s"), *NFT->GetStringField("family_id"));
				bNftFound = true;
			}
		}
		return bNftFound;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Game item not found. Item Type -> %s Item ID -> %d"), *ItemType, ItemID);
		return false;
	}
}

// Add in-game items to collection
void AddItem(FString ItemType, int ItemID, FString ItemName, FString NFTFamilyID)
{
	TSharedPtr< FJsonObject > JsonObj = MakeShareable(new FJsonObject);
	JsonObj->SetStringField("ItemType", ItemType);
	JsonObj->SetNumberField("ItemID", ItemID);
	JsonObj->SetStringField("ItemName", ItemName);
	JsonObj->SetStringField("NftFamilyID", NFTFamilyID);
	TSharedRef< FJsonValueObject > JsonValue = MakeShareable(new FJsonValueObject(JsonObj));
	GameItems.Add(JsonValue);
}

void ANavcoinSDKGameMode::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT("API response received..."));
	// Reading NFTs from API
	TSharedPtr<FJsonObject> ResponseObj;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(Reader, ResponseObj);
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT("NFTs received..."));
	UE_LOG(LogTemp, Display, TEXT("Response %s"), *Response->GetContentAsString());
	UE_LOG(LogTemp, Display, TEXT("Title: %s"), *ResponseObj->GetStringField("message"));
	NFTs = ResponseObj->GetArrayField("nfts");
	// Declaring in game items
	AddItem("PlayerSkin", 0, "Skin 1", "skin_1");
	AddItem("PlayerSkin", 1, "Skin 2", "skin_2");
	AddItem("PlayerSkin", 2, "Skin 3", "skin_3");
	// Printing NFTs to screen
	for (int32 index = 0; index < NFTs.Num(); index++)
	{
		TSharedPtr<FJsonObject> nft = NFTs[index]->AsObject();
		int32 nft_id = nft->GetIntegerField("nft_id");
		UE_LOG(LogTemp, Display, TEXT("Token ID : %s NFT ID : %d NFT Name: %s"), *nft->GetStringField("token_id"), nft_id, *nft->GetStringField("name"));
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Green, *nft->GetStringField("token_id"));
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Green, *nft->GetStringField("family_id"));
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Green, *nft->GetStringField("name"));
	}
	// Logging Game Items to Console
	for (int32 index = 0; index < GameItems.Num(); index++)
	{
		TSharedPtr<FJsonObject> nft = GameItems[index]->AsObject();
		int32 ItemID = nft->GetIntegerField("ItemID");
		UE_LOG(LogTemp, Display, TEXT("Item Type : %s Item ID : %d Item Name : %s NFT Family ID : %s"), *nft->GetStringField("ItemType"), ItemID, *nft->GetStringField("ItemName"), *nft->GetStringField("NftFamilyID"));
	}
	bool bIsItemInInventory = IsItemInInventory("PlayerSkin", 0);
	UE_LOG(LogTemp, Display, TEXT("Is NFT in inventory -> %s"), bIsItemInInventory ? TEXT("True") : TEXT("False"));
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, bIsItemInInventory ? TEXT("True") : TEXT("False"));
	bool bIsNFTAvailable = IsNFTAvailable("skin_1");
	UE_LOG(LogTemp, Display, TEXT("Is NFT available -> %s"), bIsNFTAvailable ? TEXT("True") : TEXT("False"));
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, bIsNFTAvailable ? TEXT("True") : TEXT("False"));
}