// Fill out your copyright notice in the Description page of Project Settings.


#include "GEOCameraComponent.h"
#include "GEOSceneCaptureComponent2D.h"

//VectorLookAt
#include "Kismet/KismetMathLibrary.h"

//Classes to load WorldOrigin
#include "WorldManager.h"
#include "GEOSimulatorAPIGameModeBase.h"

UGEOCameraComponent::UGEOCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	FString name = this->GetName();
	name = name.Append("SceneCapture");

	sceneCapture = CreateDefaultSubobject<UGEOSceneCaptureComponent2D>(*name);
	sceneCapture->ProjectionType = ECameraProjectionMode::Perspective;
	sceneCapture->CaptureSource = ESceneCaptureSource::SCS_SceneColorSceneDepth;

	sceneCapture->SetupAttachment(this);
}

void UGEOCameraComponent::BeginPlay()
{
    Super::BeginPlay();
    
    AGEOSimulatorAPIGameModeBase* gameMode = GetWorld()->GetAuthGameMode<AGEOSimulatorAPIGameModeBase>();
    worldManager = gameMode->GetWorldManager();
}


void UGEOCameraComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Handle LookAt
	{
		if(!NewLookAt.IsZero())
		{
			FVector ActorLocation = GetOwner()->GetActorLocation();
            
            //Parse ActorLocation to RealWorld
            FVector playerWorld = worldManager->UnrealToWorld(ActorLocation);
            FRotator rotation = UKismetMathLibrary::FindLookAtRotation(playerWorld, NewLookAt);
			
			SetRelativeRotation(rotation);
            NewLookAt = FVector::ZeroVector;
		}
	}
}

void UGEOCameraComponent::SetNewRotation(FVector LookAt)
{
	NewLookAt = LookAt;
}

UGEOSceneCaptureComponent2D* UGEOCameraComponent::GetSceneCapture()
{
	return sceneCapture;
}

UTextureRenderTarget2D* UGEOCameraComponent::GetTexture()
{
	return sceneCapture->GetTexture();
}
