// Fill out your copyright notice in the Description page of Project Settings.



#include "OnlineSubsystem/SteamGameInstance.h"


#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

USteamGameInstance::USteamGameInstance() 
{

}




void USteamGameInstance::Init()
{
	if (IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get()) {

		SessionInterface = SubSystem->GetSessionInterface();
		if (SessionInterface.IsValid()) 
		{
			//Bind Delegates Here
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &USteamGameInstance::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &USteamGameInstance::OnFindSessionsComplete);

		}
			

	}
		
}


void USteamGameInstance::OnCreateSessionComplete(FName ServerName, bool Succeeded)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete, Succeeded: %d"), Succeeded);
	if (Succeeded)
	{
		GetWorld()->ServerTravel("/Game/FirstPerson/Maps/FirstPersonMap?listen" );
	}
		
}

void USteamGameInstance::OnFindSessionsComplete(bool Succeeded)
{
	UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsComplete, Succeeded: %d"), Succeeded);
}

void USteamGameInstance::CreateServer()
{
	UE_LOG(LogTemp, Warning, TEXT("CreateServer")); 

	FOnlineSessionSettings SessionSettings;
	

	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = true;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = 10;
	SessionInterface->CreateSession(0, FName("MySession"),SessionSettings);
}

void USteamGameInstance::JoinServer()
{
	UE_LOG(LogTemp, Warning, TEXT("JoinServer"));

		SessionSearch = MakeShareable(new FOnlineSessionSearch());
		SessionSearch->bIsLanQuery = true;//Is LAN
		SessionSearch->MaxSearchResults = 10000;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());

	
}

