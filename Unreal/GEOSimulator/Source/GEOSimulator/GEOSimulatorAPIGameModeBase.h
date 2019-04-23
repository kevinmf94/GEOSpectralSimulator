// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GEOSimulatorAPIGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GEOSIMULATOR_API AGEOSimulatorAPIGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AGEOSimulatorAPIGameModeBase();
	~AGEOSimulatorAPIGameModeBase();

	//geocontrol::GEORPCServer* server;

	void BeginPlay() override;
};