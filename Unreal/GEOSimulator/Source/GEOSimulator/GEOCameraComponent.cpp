// Fill out your copyright notice in the Description page of Project Settings.

#include "GEOCameraComponent.h"
#include "GEOSceneCaptureComponent2D.h"

//Load
#include "UObject/ConstructorHelpers.h"

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

	ConstructorHelpers::FObjectFinder<UMaterial> depthObj(TEXT("/Game/PostProcess/DepthEffectMaterial.DepthEffectMaterial"));
	if (depthObj.Succeeded())
	{
		depth = depthObj.Object;
	}

	sceneCapture = CreateDefaultSubobject<UGEOSceneCaptureComponent2D>(*name);
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
            
            //Parse NewLookAt to Simulator coords
            NewLookAt = worldManager->WorldToUnreal(NewLookAt);
            FRotator rotation = UKismetMathLibrary::FindLookAtRotation(ActorLocation, NewLookAt);
			
			SetRelativeRotation(rotation);
            NewLookAt = FVector::ZeroVector;
		}
	}
}

void UGEOCameraComponent::ToggleDepth()
{
	if (!isDepth)
		ActivateDepth();
	else
		DeactivateDepth();	
}

void UGEOCameraComponent::ActivateDepth()
{
	if(!isDepth) {
		PostProcessSettings.AddBlendable(depth, 1.f);
		sceneCapture->AddShader(depth, 1.f);
		isDepth = true;
	}
}

void UGEOCameraComponent::DeactivateDepth()
{
	if(isDepth) {
		PostProcessSettings.AddBlendable(depth, 0.f);	
		sceneCapture->RemoveShader(depth);
		isDepth = false;
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
