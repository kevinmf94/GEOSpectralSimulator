// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GEOSceneCaptureComponent2D.generated.h"

/**
 * 
 */
UCLASS()
class GEOSIMULATOR_API UGEOSceneCaptureComponent2D : public USceneCaptureComponent2D
{
	GENERATED_BODY()
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
