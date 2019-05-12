// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "compiler/disable-ue4-macros.h"
#include "rpc/server.h"
#include "compiler/enable-ue4-macros.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RPCPawnServer.generated.h"

UCLASS(Abstract)
class GEOSIMULATOR_API ARPCPawnServer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARPCPawnServer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	//Server
	void StartServer();
	void StopServer();

	//rpc::server* server = nullptr;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BindFunctions(rpc::server* server);

	//Functions
	void SetLocation(double x, double y, double z);
	void SetRotationByLookAt(double x, double y, double z);

	FVector NewLocation;
	FRotator NewRotate;

	//RPCServer* server;
	rpc::server* server;
	
};
