// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VehiclePawn.h"
#include "CameraHUD.generated.h"

/**
 * 
 */
UCLASS()
class TERRAINSIMULATOR_API ACameraHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void DrawHUD() override;
	void SetTexture(UTexture* texture);

	AVehiclePawn* player;
	UCameraComponent* camera;
	
	UPROPERTY()
	UTexture* texture = nullptr;

};
