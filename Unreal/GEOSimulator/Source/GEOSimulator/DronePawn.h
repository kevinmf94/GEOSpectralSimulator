// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VehiclePawn.h"
#include "DronePawn.generated.h"

/**
 * 
 */
UCLASS()
class GEOSIMULATOR_API ADronePawn : public AVehiclePawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	ADronePawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Movement
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void Move_ZAxis(float AxisValue);
	void Rotate_ZAxis(float AxisValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void LoadMesh() override;

	//Movement vectors
	FVector CurrentVelocityXAxis;
	FVector CurrentVelocityYAxis;
	FRotator CurrentVelocityRotate;
};
