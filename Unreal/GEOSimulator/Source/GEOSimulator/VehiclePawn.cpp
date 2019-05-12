// Fill out your copyright notice in the Description page of Project Settings.

#include "VehiclePawn.h"

//Instatiante Mesh
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

//GEOClasses
#include "GEOCameraComponent.h"
#include "GEOSceneCaptureComponent2D.h"
#include "GEOSimulatorAPIGameModeBase.h"
#include "CameraHUD.h"

//Keys
#include "Classes/InputCoreTypes.h"

//SaveImage
#include "Public/ImageUtils.h"
#include "UObject/UObjectGlobals.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Serialization/Archive.h"
#include "HAL/FileManagerGeneric.h"

#include <string.h>

//Async
#include "Async.h"

// Sets default values
AVehiclePawn::AVehiclePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bEditable = true;

	//Create mesh component
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehiclePawnMesh"));
	RootComponent = staticMesh;
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

void AVehiclePawn::PostActorCreated()
{
	Super::PostActorCreated();

	if (staticMeshAsset != nullptr)
	{
		staticMesh->SetStaticMesh(staticMeshAsset);
	}
}

// Called when the game starts or when spawned
void AVehiclePawn::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("VehiclePawn BeginPlay"));

	ACameraHUD* hud = (ACameraHUD*)GetWorld()->GetFirstPlayerController()->GetHUD();
	hud->SetTexture(cameras[1]->GetTexture());
}

void AVehiclePawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AVehiclePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AVehiclePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindKey(EKeys::C, IE_Pressed, this, &AVehiclePawn::ChangeCamera);
	PlayerInputComponent->BindKey(EKeys::T, IE_Pressed, this, &AVehiclePawn::ChangeTexture);
	PlayerInputComponent->BindKey(EKeys::K, IE_Pressed, this, &AVehiclePawn::SaveImage);
}

void AVehiclePawn::BindFunctions(rpc::server* server)
{
	Super::BindFunctions(server);

	server->bind("getImage", [this](std::string text) {

		FString* str = new FString(UTF8_TO_TCHAR(text.c_str()));
		UE_LOG(LogTemp, Warning, TEXT("Save Image Path [%s]"), **str);

		AsyncTask(ENamedThreads::GameThread, [this, str]() {
			UE_LOG(LogTemp, Warning, TEXT("Save2 Image Path [%s]"), **str);
			SaveImage(**str);
			delete str;
		});

		return 1;
	});

}

FString* AVehiclePawn::BmpToJson(TArray<FColor> &bmp)
{
	FString* result = new FString(TEXT("{\"data\":["));

	for (int i = 0; i < bmp.Num(); i++)
	{
		result->Append(FString::Printf(TEXT("[ %d, %d, %d ]"), bmp[i].R, bmp[i].G, bmp[i].B));
		if (i <= bmp.Num()-2)
		{
			result->Append(TEXT(","));
		}
	}

	result->Append(TEXT("]}"));

	return result;
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

FTextureRenderTargetResource* AVehiclePawn::GetImageResource(int cameraId)
{
	UE_LOG(LogTemp, Warning, TEXT("GetImage"));

	//Capture bmp pixels
	FTextureRenderTargetResource* rt_resource = cameras[cameraId]->GetTexture()->GameThread_GetRenderTargetResource();
	FIntPoint size = rt_resource->GetSizeXY();
	return rt_resource;
}

void AVehiclePawn::GetImageBmp(FTextureRenderTargetResource* resource, TArray<FColor> &output)
{
	FReadSurfaceDataFlags flags(RCM_UNorm, CubeFace_MAX);
	flags.SetLinearToGamma(false);
	bool success = resource->ReadPixels(output, flags);
	UE_LOG(LogTemp, Warning, TEXT("ReadSucess"), success ? TEXT("OK") : TEXT("KO"));
}

void AVehiclePawn::SaveImage()
{
	SaveImage(ANSI_TO_TCHAR("C:\\Users\\Kevin\\Desktop\\prueba.png"));
}

void AVehiclePawn::SaveImage(const TCHAR* pathname)
{
	UE_LOG(LogTemp, Warning, TEXT("Save image %s"), pathname);

	//Funciona pero guarda el png en negro funciona con PF_R8G8B8A8
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	IFileHandle* fileHandle = PlatformFile.OpenWrite(pathname);
	FArchiveFileWriterGeneric archive(fileHandle, pathname, 0);
	UTextureRenderTarget2D* texture = cameras[1]->GetTexture();
	bool success = FImageUtils::ExportRenderTarget2DAsPNG(texture, archive);
	UE_LOG(LogTemp, Warning, TEXT("Save success: %s"), success ? TEXT("Success") : TEXT("Error"));
}