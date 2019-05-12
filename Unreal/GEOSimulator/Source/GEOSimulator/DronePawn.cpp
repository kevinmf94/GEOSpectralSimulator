// Fill out your copyright notice in the Description page of Project Settings.


#include "DronePawn.h"

//Instantiate Mesh
#include "UObject/ConstructorHelpers.h"

ADronePawn::ADronePawn()
{

	UE_LOG(LogTemp, Warning, TEXT("Constructor PostADronePawn"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> asset(TEXT("/Game/Drone/drone.drone"));
	if (asset.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Loaded Mesh Drone"));
		staticMeshAsset = asset.Object;
	}

	UGEOCameraComponent* cam1 = CreateCamera(FVector(-40.f, 0.0f, 10.f), FRotator(-10.0f, 0.0f, 0.0f), RootComponent);
	cameras.Add(cam1);

	UGEOCameraComponent* cam2 = CreateCamera(FVector(0.0f, 0.0f, 0.0f), FRotator(-90.0f, 0.0f, 0.0f), RootComponent);
	cameras.Add(cam2);
}

void ADronePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	PlayerInputComponent->BindAxis("MoveX", this, &ADronePawn::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &ADronePawn::Move_YAxis);
	PlayerInputComponent->BindAxis("MoveZ", this, &ADronePawn::Move_ZAxis);
	PlayerInputComponent->BindAxis("RotateZ", this, &ADronePawn::Rotate_ZAxis);
}

// Called every frame
void ADronePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Handle movement based on our "MoveX" and "MoveY" axes
	{
		if (!CurrentVelocityYAxis.IsZero() || !CurrentVelocityXAxis.IsZero())
		{
			FVector NewLocation = GetActorLocation() + (CurrentVelocityYAxis * DeltaTime) + (CurrentVelocityXAxis * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}

	{
		if (!CurrentVelocityRotate.IsZero())
		{
			FRotator NewRotation = GetActorRotation() + (CurrentVelocityRotate * DeltaTime);
			SetActorRotation(NewRotation);
		}
	}

}

// Called when the game starts or when spawned
void ADronePawn::BeginPlay()
{
	Super::BeginPlay();

}

void ADronePawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void ADronePawn::Move_XAxis(float AxisValue)
{
	// Move at 100 units per second forward or backward
	float sin;
	float cos;
	float yaw = FMath::DegreesToRadians(GetActorRotation().Yaw);
	cos = FGenericPlatformMath::Cos(yaw);
	sin = FGenericPlatformMath::Sin(yaw);
	CurrentVelocityXAxis.X = cos * AxisValue * 1000.0f;
	CurrentVelocityXAxis.Y = sin * AxisValue * 1000.0f;
	//UE_LOG(LogTemp, Warning, TEXT("CurrentVelocityXAxis: %f %f"), CurrentVelocityXAxis.X, CurrentVelocityXAxis.Y);
}

void ADronePawn::Move_YAxis(float AxisValue)
{
	// Move at 100 units per second right or left
	// Move at 100 units per second forward or backward
	float sin;
	float cos;
	float yaw = FMath::DegreesToRadians(GetActorRotation().Yaw);
	cos = FGenericPlatformMath::Cos(yaw);
	sin = FGenericPlatformMath::Sin(yaw);
	CurrentVelocityYAxis.X = sin * (AxisValue * -1.f) * 1000.0f;
	CurrentVelocityYAxis.Y = cos * AxisValue * 1000.0f;
	//UE_LOG(LogTemp, Warning, TEXT("CurrentVelocityYAxis: %f %f"), CurrentVelocityYAxis.X, CurrentVelocityYAxis.Y);
}

void ADronePawn::Move_ZAxis(float AxisValue)
{
	// Move at 100 units per second right or left
	CurrentVelocityXAxis.Z = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 1000.0f;
}

void ADronePawn::Rotate_ZAxis(float AxisValue)
{
	// Move at 100 units per second right or left
	CurrentVelocityRotate.Yaw = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}
