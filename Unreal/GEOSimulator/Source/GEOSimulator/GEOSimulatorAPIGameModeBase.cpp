// Fill out your copyright notice in the Description page of Project Settings.

#include "GEOSimulatorAPIGameModeBase.h"
#include "VehiclePawn.h"
#include "CameraHUD.h"
#include "MapChunk.h"
#include "GEOPlayerController.h"

AGEOSimulatorAPIGameModeBase::AGEOSimulatorAPIGameModeBase()
{
	DefaultPawnClass = AVehiclePawn::StaticClass();
	HUDClass = ACameraHUD::StaticClass();
	PlayerControllerClass = AGEOPlayerController::StaticClass();
}

AGEOSimulatorAPIGameModeBase::~AGEOSimulatorAPIGameModeBase()
{
}

void AGEOSimulatorAPIGameModeBase::BeginPlay()
{
	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	FTransform transform;
	//FActorSpawnParameters SpawnInfo;
	//SpawnInfo.Name = FName("Chunk1");
	//AMapChunk* chunk1 = GetWorld()->SpawnActorDeferred<AMapChunk>(Location, Rotation, SpawnInfo);

	AMapChunk* chunk1 = GetWorld()->SpawnActorDeferred<AMapChunk>(AMapChunk::StaticClass(), transform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	UE_LOG(LogTemp, Warning, TEXT("SetTexturesAndMesh"));
	chunk1->AddTexture("RGB", FPaths::ProjectDir() + "Maps/outputwms.jpg");
	chunk1->AddTexture("IR", FPaths::ProjectDir() + "Maps/outputwmsi.jpg");
	chunk1->SetMeshFile(FPaths::ProjectDir() + "Maps/outputwcs.obj");

	chunk1->FinishSpawning(transform);
}
