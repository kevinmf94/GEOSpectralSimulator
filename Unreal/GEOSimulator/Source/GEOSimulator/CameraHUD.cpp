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
    AWorldManager* manager = gameMode->GetWorldManager();
    
    worldOrigin = manager->GetWorldOrigin();
    worldOrigin.Y = -worldOrigin.Y;
}

void ACameraHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    //Get Player position
    APawn* pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if(pawn)
    {
        playerPosition = pawn->GetActorLocation();
        playerPosition.Y = -playerPosition.Y;
    }
}

void ACameraHUD::DrawHUD()
{
	if (texture)
	{
		DrawTexture(texture, 100.f, 100.f, 300.f, 300.f, 0.f, 0.f, 1.f, 1.f);
	}
    
    if(!worldOrigin.IsZero())
    {
//        UE_LOG(LogTemp, Warning, TEXT("playerPosition ACameraHUD %f %f"), playerPosition.X, playerPosition.Y);
//        UE_LOG(LogTemp, Warning, TEXT("worldOrigin ACameraHUD %f %f"), worldOrigin.X, worldOrigin.Y);
        FVector posInWorld = playerPosition+worldOrigin;
        //UE_LOG(LogTemp, Warning, TEXT("posInWorld ACameraHUD %f %f"), posInWorld.X, posInWorld.Y);
        FString txt = FString::Printf(TEXT("X: %f Y: %f Z: %f"), posInWorld.X, posInWorld.Y, posInWorld.Z);
        DrawText(txt, FColor::White, 20.f, 20.f, NULL, 1.8f);
    }
		
}

void ACameraHUD::SetTexture(UTexture* texture)
{
	this->texture = texture;
}
