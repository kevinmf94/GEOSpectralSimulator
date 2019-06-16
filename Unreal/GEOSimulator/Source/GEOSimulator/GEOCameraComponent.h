// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GEOSceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "WorldManager.h"
#include "GEOCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class GEOSIMULATOR_API UGEOCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
public:
	UGEOCameraComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
    
    virtual void BeginPlay() override;

	void SetNewRotation(FVector lookAt);

	UGEOSceneCaptureComponent2D* GetSceneCapture();
	UTextureRenderTarget2D* GetTexture();

private:

	FVector NewLookAt;

	UPROPERTY(EditAnywhere)
	UGEOSceneCaptureComponent2D* sceneCapture;
    
    AWorldManager* worldManager;
};
