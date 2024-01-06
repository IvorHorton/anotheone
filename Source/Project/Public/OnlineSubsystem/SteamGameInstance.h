// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

protected	:
	virtual void Init()	override;

	
};
