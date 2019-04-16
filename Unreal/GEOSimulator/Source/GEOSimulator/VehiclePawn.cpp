// Fill out your copyright notice in the Description page of Project Settings.

#include "VehiclePawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"

#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Public/ImageUtils.h"
#include "CameraHUD.h"

//Keys
#include "Classes/InputCoreTypes.h"

//SaveImage
#include "UObject/UObjectGlobals.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Serialization/Archive.h"
#include "HAL/FileManagerGeneric.h"

//RPC
#include "compiler/disable-ue4-macros.h"
#include "rpc/server.h"
#include "compiler/enable-ue4-macros.h"

// Sets default values
AVehiclePawn::AVehiclePawn()
{

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bEditable = true;

	//Load Mesh
	staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = staticMeshComponent;
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshAsset(TEXT("/Game/Vehicle.Vehicle"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshAsset(TEXT("/Game/Drone/drone.drone"));
	if (staticMeshAsset.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Loaded static mesh"));
		bool loaded = staticMeshComponent->SetStaticMesh(staticMeshAsset.Object);
		UE_LOG(LogTemp, Warning, TEXT("Setted Mesh: %s"), loaded ? TEXT("OK") : TEXT("NO"));
	}
	

	ourCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	ourCameraSpringArm->SetupAttachment(RootComponent);
	ourCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 1.0f), FRotator(-10, 0.0f, 0.0f));
	ourCameraSpringArm->TargetArmLength = 30.0f;
	ourCameraSpringArm->bEnableCameraLag = false;
	ourCameraSpringArm->CameraLagSpeed = 0.f;

	ourCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	ourCamera->SetupAttachment(ourCameraSpringArm);

	onBoardCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("OnBoardArm"));
	onBoardCameraArm->SetupAttachment(RootComponent);
	onBoardCameraArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-90.0f, 0.0f, 0.0f));
	onBoardCameraArm->TargetArmLength = 0.f;
	onBoardCameraArm->bEnableCameraLag = false;

	onBoardCamera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("OnBoardCamera"));
	onBoardCamera->SetupAttachment(onBoardCameraArm);

	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture_Simulator"));
	sceneCapture->SetupAttachment(onBoardCamera);
}

// Called when the game starts or when spawned
void AVehiclePawn::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("VehiclePawn BeginPlay"));
	server = new rpc::server(9999);
	server->bind("test", [](int x) { UE_LOG(LogTemp, Warning, TEXT("Called function test")); });
	server->bind("moveToXYZ", [this](double x, double y, double z) {
		MoveToXYZ(x, y, z);
	});

	UE_LOG(LogTemp, Warning, TEXT("RunServer PlayerController With Movev1"));
	server->async_run();
}

void AVehiclePawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UE_LOG(LogTemp, Warning, TEXT("VehiclePawn EndPlay"));
	server->stop();
	delete(server);
}

void AVehiclePawn::MoveToXYZ(double x, double y, double z)
{
	UE_LOG(LogTemp, Warning, TEXT("Move TO X: %f Y: %f Z: %f"), x, y, z);
	UWorld* world = GetWorld();
	APawn* pawn = world->GetFirstPlayerController()->GetPawn();
	FVector pos = pawn->GetActorLocation();
	pos.X = x;
	pos.Y = y;
	pos.Z = z;
	pawn->SetActorLocation(pos);
}


// Called every frame
void AVehiclePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Handle movement based on our "MoveX" and "MoveY" axes
	{
		if (!CurrentVelocity.IsZero())
		{
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}

	UGameViewportClient* gameViewport = GetWorld()->GetGameViewport();
	UTextureRenderTarget2D* texture = NewObject<UTextureRenderTarget2D>();
	texture->InitCustomFormat(1000, 1000, EPixelFormat::PF_FloatRGB, false);
	sceneCapture->TextureTarget = texture;
	sceneCapture->CaptureSceneDeferred();
	FTextureRenderTargetResource* rt_resource = texture->GameThread_GetRenderTargetResource();
	FIntPoint size = rt_resource->GetSizeXY();
	FReadSurfaceDataFlags flags(RCM_UNorm, CubeFace_MAX);
	flags.SetLinearToGamma(false);
	TArray<FColor> bmp;
	rt_resource->ReadPixels(bmp, flags);

	ACameraHUD* hud = (ACameraHUD*)GetWorld()->GetFirstPlayerController()->GetHUD();
	hud->SetTexture(texture);
}

// Called to bind functionality to input
void AVehiclePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	PlayerInputComponent->BindAxis("MoveX", this, &AVehiclePawn::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AVehiclePawn::Move_YAxis);
	PlayerInputComponent->BindAxis("MoveZ", this, &AVehiclePawn::Move_ZAxis);
	PlayerInputComponent->BindAction("ChangeCamera", IE_Pressed, this, &AVehiclePawn::ChangeCamera);
	//PlayerInputComponent->BindKey(EKeys::K, IE_Pressed, this, &AVehiclePawn::SaveImage);
}

void AVehiclePawn::Move_XAxis(float AxisValue)
{
	// Move at 100 units per second forward or backward
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 1000.0f;
}

void AVehiclePawn::Move_YAxis(float AxisValue)
{
	// Move at 100 units per second right or left
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 1000.0f;
}

void AVehiclePawn::Move_ZAxis(float AxisValue)
{
	// Move at 100 units per second right or left
	CurrentVelocity.Z = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 1000.0f;
}

void AVehiclePawn::ChangeCamera()
{
	UE_LOG(LogTemp, Warning, TEXT("Change camera"));
	if (firstCamera) {
		ourCamera->Deactivate();
		ourCameraSpringArm->Deactivate();
		onBoardCameraArm->Activate();
		onBoardCamera->Activate();
	} else {
		ourCamera->Activate();
		ourCameraSpringArm->Activate();
		onBoardCameraArm->Deactivate();
		onBoardCamera->Deactivate();
	}

	firstCamera = !firstCamera;
}

void AVehiclePawn::SaveImage()
{
	UE_LOG(LogTemp, Warning, TEXT("Save image"));
	UGameViewportClient* gameViewport = GetWorld()->GetGameViewport();
	UTextureRenderTarget2D* texture = NewObject<UTextureRenderTarget2D>();
	texture->InitCustomFormat(1000, 1000, EPixelFormat::PF_FloatRGB, false);
	sceneCapture->TextureTarget = texture;
	sceneCapture->CaptureSceneDeferred();
	FTextureRenderTargetResource* rt_resource = texture->GameThread_GetRenderTargetResource();
	FIntPoint size = rt_resource->GetSizeXY();
	FReadSurfaceDataFlags flags(RCM_UNorm, CubeFace_MAX);
	flags.SetLinearToGamma(false);
	TArray<FColor> bmp;
	rt_resource->ReadPixels(bmp, flags);
	
	/*TCHAR* fileName = ANSI_TO_TCHAR("C:\\prueba.png");
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	IFileHandle* fileHandle = PlatformFile.OpenWrite(fileName);
	FArchiveFileWriterGeneric archive(fileHandle, fileName, 0);
	FImageUtils::ExportRenderTarget2DAsPNG(texture, archive);*/
}