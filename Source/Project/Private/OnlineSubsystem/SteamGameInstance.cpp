// Fill out your copyright notice in the Description page of Project Settings.



#include "OnlineSubsystem/SteamGameInstance.h"

#include "Kismet/GameplayStatics.h"
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
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &USteamGameInstance::OnJoinSessionsComplete);

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

	if (Succeeded) 
	{
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
		UE_LOG(LogTemp, Warning, TEXT("SearchResults, Server Count: %d"), SearchResults.Num());
		if (SearchResults.Num()) 
		{
			UE_LOG(LogTemp, Warning, TEXT("Joining Server"));
			SessionInterface->JoinSession(0, "My Session", SearchResults[0]);
		}
			
		

	}
		
	
}

void USteamGameInstance::OnJoinSessionsComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("OnJoinSessionsComplete"));
	if (APlayerController* PController =UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FString JoinAddress = "";
		SessionInterface->GetResolvedConnectString(SessionName, JoinAddress);
		if (JoinAddress != "")
			PController->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
	}
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

