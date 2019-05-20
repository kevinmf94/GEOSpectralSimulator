// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldManager.h"
#include "Engine/World.h"
#include "GameFrameWork/PlayerController.h"
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
	
	LoadExample9x9();

	/*FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	FTransform transform;

	AMapChunk* chunk1 = GetWorld()->SpawnActorDeferred<AMapChunk>(AMapChunk::StaticClass(), transform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	UE_LOG(LogTemp, Warning, TEXT("SetTexturesAndMesh"));
	chunk1->AddTexture("RGB", FPaths::ProjectDir() + "Maps/outputwms.jpg");
	chunk1->AddTexture("IR", FPaths::ProjectDir() + "Maps/outputwmsi.jpg");
	//chunk1->AddTexture("B02", FPaths::ProjectDir() + "Maps/outputwmsb02.jpg");
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

	chunks.Add(chunk2);*/
	
}

void AWorldManager::LoadExample9x9()
{
	FTransform transform;

	FVector Correction(-20.f, -20.f, 0.f);
	FVector init(412394.118618708f, -4612149.208618707f, 0.0f);
	
	transform.SetLocation(FVector(412394.118618708f, -4612149.208618707f, 0.0f) - init);
	//transform.SetLocation(FVector(0.f, 0.f, 0.f));
	AMapChunk* chunk00 = GetWorld()->SpawnActorDeferred<AMapChunk>(AMapChunk::StaticClass(), transform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	chunk00->AddTexture("RGB", FPaths::ProjectDir() + "Maps/example9x9/outputwms00.jpg");
	chunk00->AddTexture("IR", FPaths::ProjectDir() + "Maps/example9x9/outputwmsi00.jpg");
	chunk00->SetMeshFile(FPaths::ProjectDir() + "Maps/example9x9/outputwcs00.obj");
	chunk00->FinishSpawning(transform);
	chunks.Add(chunk00);

	//transform.SetLocation(FVector(300.f*5.f, 0.f, 0.f));
	transform.SetLocation(FVector(413894.11861870793f, -4612149.208618708f, 0.0f) - init + Correction);
	AMapChunk* chunk01 = GetWorld()->SpawnActorDeferred<AMapChunk>(AMapChunk::StaticClass(), transform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	chunk01->AddTexture("RGB", FPaths::ProjectDir() + "Maps/example9x9/outputwms01.jpg");
	chunk01->AddTexture("IR", FPaths::ProjectDir() + "Maps/example9x9/outputwmsi01.jpg");
	chunk01->SetMeshFile(FPaths::ProjectDir() + "Maps/example9x9/outputwcs01.obj");
	chunk01->FinishSpawning(transform);
	chunks.Add(chunk01);

	transform.SetLocation(FVector(415394.118618708f, -4612149.208618708f, 0.0f) - init + Correction);
	AMapChunk* chunk02 = GetWorld()->SpawnActorDeferred<AMapChunk>(AMapChunk::StaticClass(), transform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	chunk02->AddTexture("RGB", FPaths::ProjectDir() + "Maps/example9x9/outputwms02.jpg");
	chunk02->AddTexture("IR", FPaths::ProjectDir() + "Maps/example9x9/outputwmsi02.jpg");
	chunk02->SetMeshFile(FPaths::ProjectDir() + "Maps/example9x9/outputwcs02.obj");
	chunk02->FinishSpawning(transform);
	chunks.Add(chunk02);

	transform.SetLocation(FVector(412394.11861870793f, -4610649.208618708f, 0.0f) - init + Correction);
	AMapChunk* chunk10 = GetWorld()->SpawnActorDeferred<AMapChunk>(AMapChunk::StaticClass(), transform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	chunk10->AddTexture("RGB", FPaths::ProjectDir() + "Maps/example9x9/outputwms10.jpg");
	chunk10->AddTexture("IR", FPaths::ProjectDir() + "Maps/example9x9/outputwmsi10.jpg");
	chunk10->SetMeshFile(FPaths::ProjectDir() + "Maps/example9x9/outputwcs10.obj");
	chunk10->FinishSpawning(transform);
	chunks.Add(chunk10);

	transform.SetLocation(FVector(413894.11861870793f, -4610649.208618708f, 0.0f) - init + Correction);
	AMapChunk* chunk11 = GetWorld()->SpawnActorDeferred<AMapChunk>(AMapChunk::StaticClass(), transform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	chunk11->AddTexture("RGB", FPaths::ProjectDir() + "Maps/example9x9/outputwms11.jpg");
	chunk11->AddTexture("IR", FPaths::ProjectDir() + "Maps/example9x9/outputwmsi11.jpg");
	chunk11->SetMeshFile(FPaths::ProjectDir() + "Maps/example9x9/outputwcs11.obj");
	chunk11->FinishSpawning(transform);
	chunks.Add(chunk11);

	transform.SetLocation(FVector(415394.11861870793f, -4610649.208618708f, 0.0f) - init + Correction);
	AMapChunk* chunk12 = GetWorld()->SpawnActorDeferred<AMapChunk>(AMapChunk::StaticClass(), transform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	chunk12->AddTexture("RGB", FPaths::ProjectDir() + "Maps/example9x9/outputwms12.jpg");
	chunk12->AddTexture("IR", FPaths::ProjectDir() + "Maps/example9x9/outputwmsi12.jpg");
	chunk12->SetMeshFile(FPaths::ProjectDir() + "Maps/example9x9/outputwcs12.obj");
	chunk12->FinishSpawning(transform);
	chunks.Add(chunk12);

	transform.SetLocation(FVector(412394.11861870793f, -4609149.208618708f, 0.0f) - init + Correction);
	AMapChunk* chunk20 = GetWorld()->SpawnActorDeferred<AMapChunk>(AMapChunk::StaticClass(), transform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	chunk20->AddTexture("RGB", FPaths::ProjectDir() + "Maps/example9x9/outputwms20.jpg");
	chunk20->AddTexture("IR", FPaths::ProjectDir() + "Maps/example9x9/outputwmsi20.jpg");
	chunk20->SetMeshFile(FPaths::ProjectDir() + "Maps/example9x9/outputwcs20.obj");
	chunk20->FinishSpawning(transform);
	chunks.Add(chunk20);

	transform.SetLocation(FVector(413894.11861870793f, -4609149.208618708f, 0.0f) - init + Correction);
	AMapChunk* chunk21 = GetWorld()->SpawnActorDeferred<AMapChunk>(AMapChunk::StaticClass(), transform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	chunk21->AddTexture("RGB", FPaths::ProjectDir() + "Maps/example9x9/outputwms21.jpg");
	chunk21->AddTexture("IR", FPaths::ProjectDir() + "Maps/example9x9/outputwmsi21.jpg");
	chunk21->SetMeshFile(FPaths::ProjectDir() + "Maps/example9x9/outputwcs21.obj");
	chunk21->FinishSpawning(transform);
	chunks.Add(chunk21);

	transform.SetLocation(FVector(415394.11861870793f, -4609149.208618709f, 0.0f) - init + Correction);
	AMapChunk* chunk22 = GetWorld()->SpawnActorDeferred<AMapChunk>(AMapChunk::StaticClass(), transform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	chunk22->AddTexture("RGB", FPaths::ProjectDir() + "Maps/example9x9/outputwms22.jpg");
	chunk22->AddTexture("IR", FPaths::ProjectDir() + "Maps/example9x9/outputwmsi22.jpg");
	chunk22->SetMeshFile(FPaths::ProjectDir() + "Maps/example9x9/outputwcs22.obj");
	chunk22->FinishSpawning(transform);
	chunks.Add(chunk22);

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
