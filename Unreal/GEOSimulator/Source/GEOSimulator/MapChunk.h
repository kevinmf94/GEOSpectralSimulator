// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Components/InputComponent.h"
#include "MapChunk.generated.h"

UCLASS()
class GEOSIMULATOR_API AMapChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapChunk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeTexture(FName textureName);
	
	void PostActorCreated() override;
	void PostLoad() override;
	void LoadMeshFile();
	void LoadTextures();
    TArray<FName> GetTexturesNames();

	//Setters
	void AddTexture(FName param, FString pathfile);
	void SetMeshFile(FString pathfile);

private:

	UPROPERTY(EditAnywhere)
	UProceduralMeshComponent* mesh;

	UMaterial* material;

	UPROPERTY(EditAnywhere)
	UMaterialInstanceDynamic* materialDynamic;

	UPROPERTY(EditAnywhere)
	TMap<FName, FString> texturesFiles;

	UPROPERTY(EditAnywhere)
	FString meshFile;
    
    TMap<FName, UTexture2D*> textureMap;
    FName textureSelected;
};
