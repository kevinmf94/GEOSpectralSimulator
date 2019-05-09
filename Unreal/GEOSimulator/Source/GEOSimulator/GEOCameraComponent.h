// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GEOCameraComponent.generated.h"

class UGEOSceneCaptureComponent2D;

/**
 * 
 */
UCLASS()
class GEOSIMULATOR_API UGEOCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
public:
	UGEOCameraComponent();

	UGEOSceneCaptureComponent2D* GetSceneCapture();

private:
	UPROPERTY()
	UGEOSceneCaptureComponent2D* sceneCapture;
};
