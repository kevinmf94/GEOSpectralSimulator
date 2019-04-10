// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraHUD.h"
#include "Engine/World.h"
#include "Engine/GameViewportClient.h"
#include "VehiclePawn.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"

void ACameraHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = this->GetWorld();
	UGameViewportClient* viewPort = world->GetGameViewport();

	APlayerController* controller = world->GetFirstPlayerController();
	player = (AVehiclePawn*) controller->GetPawn();
	camera = player->onBoardCamera;
}

void ACameraHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ACameraHUD::DrawHUD()
{
	if (texture)
	{
		DrawTexture(texture, 100.f, 100.f, 200.f, 200.f, 0.f, 0.f, 1.f, 1.f);
	}
		
}

void ACameraHUD::SetTexture(UTexture* texture)
{
	this->texture = texture;
}