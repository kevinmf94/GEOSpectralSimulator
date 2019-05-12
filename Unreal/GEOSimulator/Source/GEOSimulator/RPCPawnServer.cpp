// Fill out your copyright notice in the Description page of Project Settings.

#include "RPCPawnServer.h"

//Keys
#include "Components/InputComponent.h"
#include "Classes/InputCoreTypes.h"
#include "Framework/Commands/InputChord.h"

// Sets default values
ARPCPawnServer::ARPCPawnServer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARPCPawnServer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARPCPawnServer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (server != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ARPCPawnServer EndPlay StopServer()"));
		StopServer();
	}
	UE_LOG(LogTemp, Warning, TEXT("ARPCPawnServer EndPlay"));
}

// Called every frame
void ARPCPawnServer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Handle new location
	{
		if (!NewLocation.IsZero())
		{
			SetActorLocation(NewLocation);
			NewLocation = FVector::ZeroVector;
		}
	}
}

void ARPCPawnServer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindKey(EKeys::Y, IE_Pressed, this, &ARPCPawnServer::StartServer);
	PlayerInputComponent->BindKey(EKeys::U, IE_Pressed, this, &ARPCPawnServer::StopServer);
}

void ARPCPawnServer::StartServer()
{
	UE_LOG(LogTemp, Warning, TEXT("ARPCPawnServer StartServer"));
	//server = RPCServer::GetInstance();
	//server->InitServer(9999);
	//BindFunctions(server);
	//server->StartServer();
	
	if (!server)
	{
		server = new rpc::server(9999);
		BindFunctions(server);
		UE_LOG(LogTemp, Warning, TEXT("Server started!"));
		server->async_run();
	}
}

void ARPCPawnServer::StopServer()
{
	UE_LOG(LogTemp, Warning, TEXT("ARPCPawnServer StopServer"));

	if (server)
	{
		server->close_sessions();
		server->stop();
		delete server;
		server = nullptr;
	}
	
}

void ARPCPawnServer::BindFunctions(rpc::server* server)
{
	server->bind("test", [](int x) { UE_LOG(LogTemp, Warning, TEXT("Called function test")); });
	server->bind("setLocation", [this](double x, double y, double z) {
		SetLocation(x, y, z);
		});
	server->bind("setRotation", [this](double x, double y, double z) {
		SetRotationByLookAt(x, y, z);
		});
	server->bind("setLocationAndRotation", [this](double x, double y, double z) {
		SetLocation(x, y, z);
	});
}


void ARPCPawnServer::SetLocation(double x, double y, double z)
{
	UE_LOG(LogTemp, Warning, TEXT("Move TO X: %f Y: %f Z: %f"), x, y, z);
	NewLocation.X = x;
	NewLocation.Y = y;
	NewLocation.Z = z;
}

void ARPCPawnServer::SetRotationByLookAt(double x, double y, double z)
{
	//TODO
}

