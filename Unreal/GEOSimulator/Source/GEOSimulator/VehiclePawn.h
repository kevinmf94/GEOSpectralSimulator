// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "compiler/disable-ue4-macros.h"
#include "rpc/server.h"
#include "compiler/enable-ue4-macros.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GEOCameraComponent.h"
#include "VehiclePawn.generated.h"

class UCameraComponent;

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

	virtual void LoadMesh();
	UGEOCameraComponent* CreateCamera(FVector position, FRotator rotation, USceneComponent* root);
	void ChangeCamera();
	void ChangeTexture();
	void SaveImage();

	int indexCamera = 1;

	void MoveToXYZ(double x, double y, double z);

	void StartServer();
	void StopServer();

	FVector MoveLocation;

	UPROPERTY(EditAnywhere)
	TArray<UGEOCameraComponent*> cameras;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* staticMesh;

	UPROPERTY(EditAnywhere)
	class UTextureRenderTarget2D* texture;

	rpc::server* server = nullptr;
};
