// Fill out your copyright notice in the Description page of Project Settings.

#include "VehiclePawn.h"

//Instatiante Mesh
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

//GEOClasses
#include "GEOCameraComponent.h"
#include "GEOSceneCaptureComponent2D.h"
#include "CameraHUD.h"
#include "GEOSimulatorAPIGameModeBase.h"

//Keys
#include "Classes/InputCoreTypes.h"
#include "Framework/Commands/InputChord.h"

//SaveImage
#include "Engine/TextureRenderTarget2D.h"
#include "Public/ImageUtils.h"

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
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehiclePawnMesh"));
	RootComponent = staticMesh;

	LoadMesh();

	UGEOCameraComponent* cam1 = CreateCamera(FVector(0.0f, 0.0f, 0.0f), FRotator(-90.0f, 0.0f, 0.0f), RootComponent);
	cameras.Add(cam1);
}

UGEOCameraComponent* AVehiclePawn::CreateCamera(FVector position, FRotator rotation, USceneComponent* Root)
{
	FName CameraName = *(FString::Printf(TEXT("GameCamera_%u"), indexCamera));
	FName SceneCaptureName = *(FString::Printf(TEXT("SceneCapture_%u"), indexCamera));
	indexCamera++;

	UGEOCameraComponent* camera = CreateDefaultSubobject<UGEOCameraComponent>(CameraName);
	camera->SetRelativeLocationAndRotation(position, rotation);
	camera->SetupAttachment(Root);

	return camera;
}

void AVehiclePawn::LoadMesh()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshAsset(TEXT("/Game/Vehicle.Vehicle"));
	if (staticMeshAsset.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Loaded static mesh"));
		bool loaded = staticMesh->SetStaticMesh(staticMeshAsset.Object);
		UE_LOG(LogTemp, Warning, TEXT("Setted Mesh: %s"), loaded ? TEXT("OK") : TEXT("NO"));
	}
}

// Called when the game starts or when spawned
void AVehiclePawn::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("VehiclePawn BeginPlay"));

	texture = NewObject<UTextureRenderTarget2D>();
	//texture->InitAutoFormat(1000, 1000);
	texture->InitCustomFormat(1000, 1000, PF_B8G8R8A8, false);
	cameras[0]->GetSceneCapture()->TextureTarget = texture;
	//sceneCapture->CaptureSceneDeferred();

	ACameraHUD* hud = (ACameraHUD*)GetWorld()->GetFirstPlayerController()->GetHUD();
	hud->SetTexture(texture);
}

void AVehiclePawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (server != nullptr)
	{
		StopServer();
	}
	UE_LOG(LogTemp, Warning, TEXT("VehiclePawn EndPlay"));
}

void AVehiclePawn::MoveToXYZ(double x, double y, double z)
{
	UE_LOG(LogTemp, Warning, TEXT("Move TO X: %f Y: %f Z: %f"), x, y, z);
	MoveLocation.X = x;
	MoveLocation.Y = y;
	MoveLocation.Z = z;
}

// Called every frame
void AVehiclePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Handle new location
	{
		if (!MoveLocation.IsZero())
		{
			SetActorLocation(MoveLocation);
			MoveLocation = FVector::ZeroVector;
		}
	}
}

// Called to bind functionality to input
void AVehiclePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindKey(EKeys::C, IE_Pressed, this, &AVehiclePawn::ChangeCamera);
	PlayerInputComponent->BindKey(EKeys::T, IE_Pressed, this, &AVehiclePawn::ChangeTexture);
	PlayerInputComponent->BindKey(EKeys::K, IE_Pressed, this, &AVehiclePawn::SaveImage);
	PlayerInputComponent->BindKey(EKeys::Y, IE_Pressed, this, &AVehiclePawn::StartServer);
	PlayerInputComponent->BindKey(EKeys::U, IE_Pressed, this, &AVehiclePawn::StopServer);
}

void AVehiclePawn::StartServer()
{
	if (server == nullptr)
	{
		server = new rpc::server(9999);
		server->bind("test", [](int x) { UE_LOG(LogTemp, Warning, TEXT("Called function test")); });
		server->bind("moveToXYZ", [this](double x, double y, double z) {
			MoveToXYZ(x, y, z);
		});

		UE_LOG(LogTemp, Warning, TEXT("Server started!"));
		server->async_run();
	}	
}

void AVehiclePawn::StopServer()
{
	if (server != nullptr)
	{
		server->stop();
		delete(server);
		server = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("Stop server!"));
	}
}

void AVehiclePawn::ChangeCamera()
{
	UE_LOG(LogTemp, Warning, TEXT("Change camera"));
	//TODO: Change camera
}

void AVehiclePawn::ChangeTexture()
{
	UE_LOG(LogTemp, Warning, TEXT("Change texture"));
	AGEOSimulatorAPIGameModeBase* gameMode = GetWorld()->GetAuthGameMode<AGEOSimulatorAPIGameModeBase>();
	AWorldManager* manager = gameMode->GetWorldManager();
	manager->ChangeTexture();
}

void AVehiclePawn::SaveImage()
{
	UE_LOG(LogTemp, Warning, TEXT("Save image"));

	//Capture bmp pixels
	FTextureRenderTargetResource* rt_resource = texture->GameThread_GetRenderTargetResource();
	FIntPoint size = rt_resource->GetSizeXY();
	FReadSurfaceDataFlags flags(RCM_UNorm, CubeFace_MAX);
	flags.SetLinearToGamma(false);
	TArray<FColor> bmp;
	bool success = rt_resource->ReadPixels(bmp, flags);
	
	UE_LOG(LogTemp, Warning, TEXT("X: %d Y: %d"), size.X, size.Y);
	UE_LOG(LogTemp, Warning, TEXT("ReadSucess"), success ? TEXT("OK") : TEXT("KO"));
	int32 r = bmp[0].R;
	int32 g = bmp[0].G;
	int32 b = bmp[0].B;
	UE_LOG(LogTemp, Warning, TEXT("Tick Pixel 0,0: %d %d %d"), r, g, b);
	
	//Funciona pero guarda el png en negro funciona con PF_R8G8B8A8
	TCHAR* fileName = ANSI_TO_TCHAR("C:\\Users\\Kevin\\Desktop\\prueba.png");
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	IFileHandle* fileHandle = PlatformFile.OpenWrite(fileName);
	FArchiveFileWriterGeneric archive(fileHandle, fileName, 0);
	success = FImageUtils::ExportRenderTarget2DAsPNG(texture, archive);
	UE_LOG(LogTemp, Warning, TEXT("Save success: %s"), success ? TEXT("Success") : TEXT("Error"));
}