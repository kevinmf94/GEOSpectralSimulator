// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "compiler/disable-ue4-macros.h"
#include "rpc/server.h"
#include "compiler/enable-ue4-macros.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VehiclePawn.generated.h"

UCLASS()
class GEOSIMULATOR_API AVehiclePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVehiclePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Movement
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void Move_ZAxis(float AxisValue);
	void Rotate_ZAxis(float AxisValue);
	void ChangeCamera();
	void SaveImage();

	void MoveToXYZ(double x, double y, double z);

	void StartServer();
	void StopServer();

	FVector CurrentVelocityXAxis;
	FVector CurrentVelocityYAxis;
	FRotator CurrentVelocityRotate;
	FVector MoveLocation;
	bool firstCamera = true;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* staticMeshComponent;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* ourCameraSpringArm;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* ourCamera;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* onBoardCameraArm;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* onBoardCamera;

	UPROPERTY(EditAnywhere)
	class USceneCaptureComponent2D* sceneCapture;

	class UTextureRenderTarget2D* texture;

	rpc::server* server = nullptr;
};
