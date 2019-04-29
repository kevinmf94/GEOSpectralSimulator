// Fill out your copyright notice in the Description page of Project Settings.


#include "MapChunk.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMapChunk::AMapChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

}

// Called when the game starts or when spawned
void AMapChunk::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

