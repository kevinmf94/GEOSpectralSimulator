// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPCPawnServer.h"
#include "GEOCameraComponent.h"
#include "VehiclePawn.generated.h"

class UCameraComponent;

UCLASS(Abstract)
class GEOSIMULATOR_API AVehiclePawn : public ARPCPawnServer
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVehiclePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostActorCreated() override;

	UStaticMesh* staticMeshAsset = nullptr;
private:
	int indexCamera = 1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BindFunctions(rpc::server* server) override;

	UGEOCameraComponent* CreateCamera(FVector position, FRotator rotation, USceneComponent* root);
	void ChangeCamera();
	void ChangeTexture();
	void SaveImage();
	void SaveImage(const TCHAR* pathname);
	FTextureRenderTargetResource* GetImageResource(int camera);
	void GetImageBmp(FTextureRenderTargetResource* resource, TArray<FColor>& output);

	static FString* BmpToJson(TArray<FColor>& bmp);

	UPROPERTY(EditAnywhere)
	TArray<UGEOCameraComponent*> cameras;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* staticMesh;
};
