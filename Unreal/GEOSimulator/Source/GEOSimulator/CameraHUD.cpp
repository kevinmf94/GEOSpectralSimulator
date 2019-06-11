// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraHUD.h"
#include "GEOSimulatorAPIGameModeBase.h"
#include "WorldManager.h"
#include "Containers/UnrealString.h"
#include "Engine/World.h"

void ACameraHUD::BeginPlay()
{
	Super::BeginPlay();
    
    AGEOSimulatorAPIGameModeBase* gameMode = GetWorld()->GetAuthGameMode<AGEOSimulatorAPIGameModeBase>();
    worldManager = gameMode->GetWorldManager();
}

void ACameraHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    //Get Player position
    APawn* pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if(pawn)
    {
        playerPosition = pawn->GetActorLocation();
    }
}

void ACameraHUD::DrawHUD()
{
	if (texture)
	{
		DrawTexture(texture, 100.f, 100.f, 300.f, 300.f, 0.f, 0.f, 1.f, 1.f);
	}
    
    FVector posInWorld = worldManager->UnrealToWorld(playerPosition);
    FString txt = FString::Printf(TEXT("X: %f Y: %f Z: %f"), posInWorld.X, posInWorld.Y, posInWorld.Z);
    DrawText(txt, FColor::White, 20.f, 20.f, NULL, 1.8f);
		
}

void ACameraHUD::SetTexture(UTexture* texture)
{
	this->texture = texture;
}
