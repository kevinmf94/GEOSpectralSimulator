// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldManager.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
#include "MapChunk.h"

// Sets default values
AWorldManager::AWorldManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldManager::BeginPlay()
{
	Super::BeginPlay();

	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	FTransform transform;

	AMapChunk* chunk1 = GetWorld()->SpawnActorDeferred<AMapChunk>(AMapChunk::StaticClass(), transform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	UE_LOG(LogTemp, Warning, TEXT("SetTexturesAndMesh"));
	chunk1->AddTexture("RGB", FPaths::ProjectDir() + "Maps/outputwms.jpg");
	chunk1->AddTexture("IR", FPaths::ProjectDir() + "Maps/outputwmsi.jpg");
	chunk1->AddTexture("B02", FPaths::ProjectDir() + "Maps/outputwmsb02.jpg");
	chunk1->SetMeshFile(FPaths::ProjectDir() + "Maps/outputwcs.obj");
	chunk1->FinishSpawning(transform);

	chunks.Add(chunk1);

	FVector Location2(1250.0f, 0.0f, 0.0f);

	transform.SetLocation(Location2);
	AMapChunk* chunk2 = GetWorld()->SpawnActorDeferred<AMapChunk>(AMapChunk::StaticClass(), transform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	UE_LOG(LogTemp, Warning, TEXT("SetTexturesAndMesh"));
	chunk2->AddTexture("RGB", FPaths::ProjectDir() + "Maps/outputwms2.jpg");
	chunk2->AddTexture("IR", FPaths::ProjectDir() + "Maps/outputwmsi2.jpg");
	chunk2->SetMeshFile(FPaths::ProjectDir() + "Maps/outputwcs2.obj");
	chunk2->FinishSpawning(transform);

	chunks.Add(chunk2);
	
}

// Called every frame
void AWorldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<AMapChunk*> AWorldManager::GetChunks()
{
	return chunks;
}

void AWorldManager::ChangeTexture()
{
	NextTexture(textureSelected);
	UE_LOG(LogTemp, Warning, TEXT("NewTexture %d"), textureSelected);

	for (int i = 0; i < chunks.Num(); i++)
	{
		chunks[i]->ChangeTexture(textureSelected);
	}
}

void AWorldManager::NextTexture(TextureSelected& textureActual)
{
	switch (textureActual)
	{
	case RGB:
		textureActual = IR;
		break;
	case IR:
		textureActual = B01;
		break;
	case B01:
		textureActual = B02;
		break;
	case B02:
		textureActual = RGB;
		break;
	}
}
