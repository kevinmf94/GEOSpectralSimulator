// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapChunk.h"
#include "WorldManager.generated.h"

class AMapChunk;

UCLASS()
class GEOSIMULATOR_API AWorldManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<AMapChunk*> chunks;
private:
	TextureSelected textureSelected = TextureSelected::RGB;

	static void NextTexture(TextureSelected& textureActual);

	void LoadExample9x9();
    void LoadFile(FString path, FString fileName);
    
    FVector worldOrigin;
    
    FString folderMap;
    FString map;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<AMapChunk*> GetChunks();
	void ChangeTexture();
    
    FVector GetWorldOrigin();
    
    FVector WorldToUnreal(FVector vector);
    FVector UnrealToWorld(FVector vector);
};
