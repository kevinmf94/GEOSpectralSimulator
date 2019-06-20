// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraHUD.h"
#include "GEOSimulatorAPIGameModeBase.h"
#include "WorldManager.h"
#include "Containers/UnrealString.h"
#include "RPCPawnServer.h"
#include "Engine/World.h"

void ACameraHUD::BeginPlay()
{
	Super::BeginPlay();
    
}

void ACameraHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    //Get Player position
    APawn* pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if(pawn)
    {
        playerPosition = pawn->GetActorLocation();
        isRunningServer = ((ARPCPawnServer*) pawn)->IsServerRunning();
    }
    
    if(!worldManager)
    {
        AGEOSimulatorAPIGameModeBase* gameMode = GetWorld()->GetAuthGameMode<AGEOSimulatorAPIGameModeBase>();
        worldManager = gameMode->GetWorldManager();
    }
}

void ACameraHUD::DrawHUD()
{
	if (texture)
	{
		DrawTexture(texture, 100.f, 100.f, 300.f, 300.f, 0.f, 0.f, 1.f, 1.f);
	}
    
    if(worldManager)
    {
        FVector posInWorld = worldManager->UnrealToWorld(playerPosition);
        FString txt = FString::Printf(TEXT("X: %f Y: %f Z: %f"), posInWorld.X, posInWorld.Y, posInWorld.Z);
        DrawText(txt, FColor::White, 20.f, 20.f, NULL, 1.4f);
        
        FName textureSelected = worldManager->GetTextureSelected();
        FString txt2 = FString::Printf(TEXT("Texture Selected: %s"), *(textureSelected.ToString()));
        DrawText(txt2, FColor::White, 20.f, 60.f, NULL, 1.4f);
    }
    
    FString serverState = FString::Printf(TEXT("Server state: %s"), isRunningServer ? TEXT("Running") : TEXT("Off"));
    DrawText(serverState, FColor::White, 20.f, 40.f, NULL, 1.4f);
}

void ACameraHUD::SetTexture(UTexture* texture)
{
	this->texture = texture;
}
