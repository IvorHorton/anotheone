// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define SEARCH_PRESENCE TEXT("SEARCH_PRESENCE")

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "SteamGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API USteamGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	USteamGameInstance();

protected:

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	

	virtual void Init()	override;

	virtual void OnCreateSessionComplete(FName ServerName, bool Succeeded); ;
	virtual void OnFindSessionsComplete(bool Succeeded);

	UFUNCTION(BlueprintCallable)
	void CreateServer();

	UFUNCTION(BlueprintCallable)
	void JoinServer();
	
};
