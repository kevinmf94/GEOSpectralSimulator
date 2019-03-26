// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimulatorGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TERRAINSIMULATOR_API ASimulatorGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ASimulatorGameMode();

	void BeginPlay() override;
};
