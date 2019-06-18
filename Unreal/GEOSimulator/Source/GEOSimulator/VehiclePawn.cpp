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
#include <queue>
#include "Engine/GameViewportClient.h"

//Async
#include "Async.h"
#include "Async/Future.h"

//VectorLookAt
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AVehiclePawn::AVehiclePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
#if WITH_EDITOR
	bEditable = true;
#endif

	//Create mesh component
	staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehiclePawnMesh"));
	RootComponent = staticMeshComponent;
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

	if (staticMesh != nullptr)
	{
		staticMeshComponent->SetStaticMesh(staticMesh);
	}
}

// Called when the game starts or when spawned
void AVehiclePawn::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("VehiclePawn BeginPlay"));

	ACameraHUD* hud = (ACameraHUD*)GetWorld()->GetFirstPlayerController()->GetHUD();
	hud->SetTexture(cameras[1]->GetTexture());
    
    AGEOSimulatorAPIGameModeBase* gameMode = GetWorld()->GetAuthGameMode<AGEOSimulatorAPIGameModeBase>();
    worldManager = gameMode->GetWorldManager();
}

void AVehiclePawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AVehiclePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Handle new location
	{
		if (!NewLocation.IsZero())
		{
			SetActorLocation(worldManager->WorldToUnreal(NewLocation));
			NewLocation = FVector::ZeroVector;
		}
	}

	//Handle LookAt
	{
		if (!NewLookAt.IsZero())
		{
			FVector ActorLocation = GetActorLocation();
            
            
            NewLookAt = worldManager->WorldToUnreal(NewLookAt);
			FRotator rotation = UKismetMathLibrary::FindLookAtRotation(ActorLocation, NewLookAt);
			SetActorRotation(rotation);
            
			NewLookAt = FVector::ZeroVector;
		}
	}
    
    //Handle images requests
    {
        /* while(requests.size() > 0)
        {
            ImageRequest element = requests.front();
			worldManager->ChangeTexture(element.texture);

			requests.pop();
            SaveImage(element.cameraId, *(element.path));
            element.promise->SetValue(1);

		}*/
    }
}

// Called to bind functionality to input
void AVehiclePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindKey(EKeys::C, IE_Pressed, this, &AVehiclePawn::ChangeCamera);
	PlayerInputComponent->BindKey(EKeys::T, IE_Pressed, this, &AVehiclePawn::ChangeTexture);
	PlayerInputComponent->BindKey(EKeys::K, IE_Pressed, this, &AVehiclePawn::SaveImage);
	PlayerInputComponent->BindKey(EKeys::H, IE_Pressed, this, &AVehiclePawn::HiddenVehicle);
	PlayerInputComponent->BindKey(EKeys::B, IE_Pressed, this, &AVehiclePawn::ToggleDepth);
}

void AVehiclePawn::ToggleDepth()
{
	if(!isDepth)
		ActivateDepth();
	else
		DeactivateDepth();
}

void AVehiclePawn::ActivateDepth()
{
	for(int i = 0; i < cameras.Num(); i++)
	{
		cameras[i]->ActivateDepth();
	}
	isDepth = true;
}

void AVehiclePawn::DeactivateDepth()
{
	for(int i = 0; i < cameras.Num(); i++)
	{
		cameras[i]->DeactivateDepth();
	}
	isDepth = false;
}

void AVehiclePawn::BindFunctions(rpc::server* server)
{
	Super::BindFunctions(server);

	server->bind("setLocation", [this](double x, double y, double z) {
		SetLocation(x, y, z);
	});

	server->bind("setLookAt", [this](double x, double y, double z) {
		SetRotationByLookAt(x, y, z);
	});

	server->bind("setLocationAndLookAt", [this](double x, double y, double z, double xl, double yl, double zl) {
		SetLocation(x, y, z);
		SetRotationByLookAt(xl, yl, zl);
	});

	server->bind("setCameraLookAt", [this](int cameraId, double x, double y, double z) {
		SetCameraLookAt(cameraId, x, y, z);
	});

	server->bind("getImage", [this](int cameraId, std::string text, std::string textureName) {

		FString str(UTF8_TO_TCHAR(text.c_str()));
		FName txtName(UTF8_TO_TCHAR(textureName.c_str()));
        promise = new TPromise<int>();
        TFuture<int> future = promise->GetFuture();

		if(worldManager->IsValidTexture(txtName))
		{
			
			AsyncTask(ENamedThreads::GameThread, [this, &str, txtName, cameraId]() {
				check(IsInGameThread());

				FName actualTexture = this->worldManager->GetTextureSelected();
				if(txtName == FName(TEXT("depth")))
				{
					this->ActivateDepth();
				} else 
				{
					this->worldManager->ChangeTexture(txtName);
				}

				game_viewport_ = GetWorld()->GetGameViewport();
				bool saved_DisableWorldRendering_ = game_viewport_->bDisableWorldRendering;
				game_viewport_->bDisableWorldRendering = 0;
				
				end_draw_handle_ = game_viewport_->OnEndDraw().AddLambda([this, &str, saved_DisableWorldRendering_, cameraId, txtName, actualTexture] {
					check(IsInGameThread());

					game_viewport_->OnEndDraw().Remove(end_draw_handle_);
				
					UE_LOG(LogTemp, Warning, TEXT("Save Image Path [%s]"));
					SaveImage(cameraId, *str);
					UE_LOG(LogTemp, Warning, TEXT("Saved Image"));
					
					game_viewport_->bDisableWorldRendering = saved_DisableWorldRendering_;

					if(txtName == FName(TEXT("depth")))
						this->DeactivateDepth();
					else
						this->worldManager->ChangeTexture(actualTexture);

					end_draw_handle2_ = game_viewport_->OnEndDraw().AddLambda([this] {
						game_viewport_->OnEndDraw().Remove(end_draw_handle2_);
						this->promise->SetValue(1);
					});
				});
				
        	});

			future.Get();
			delete promise;
		}
		
        return 1;
	});

}

void AVehiclePawn::HiddenVehicle()
{
	UE_LOG(LogTemp, Warning, TEXT("Toogle StaticMesh"));
	staticMeshComponent->ToggleVisibility();
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

void AVehiclePawn::SetLocation(double x, double y, double z)
{
	UE_LOG(LogTemp, Warning, TEXT("Move TO X: %f Y: %f Z: %f"), x, y, z);
	NewLocation.X = x;
	NewLocation.Y = y;
	NewLocation.Z = z;
}

void AVehiclePawn::SetRotationByLookAt(double x, double y, double z)
{
	UE_LOG(LogTemp, Warning, TEXT("LookAt TO X: %f Y: %f Z: %f"), x, y, z);
	NewLookAt.X = x;
	NewLookAt.Y = y;
	NewLookAt.Z = z;
}

void AVehiclePawn::SetCameraLookAt(int cameraId, double x, double y, double z)
{
	UE_LOG(LogTemp, Warning, TEXT("CameraID: %d LookAt TO X: %f Y: %f Z: %f"), cameraId, x, y, z);
	if(cameras.Num() > cameraId)
	{	
		cameras[cameraId]->SetNewRotation(FVector(x, y, z));
	}
}

/**
* Save Images
*/
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
	SaveImage(1, *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()+ANSI_TO_TCHAR("Output.png")));
}

void AVehiclePawn::SaveImage(int cameraId, const TCHAR* pathname)
{
	UE_LOG(LogTemp, Warning, TEXT("Save image %s"), pathname);
	UTextureRenderTarget2D* texture = cameras[cameraId]->GetTexture();

	//Funciona pero guarda el png en negro funciona con PF_R8G8B8A8
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	IFileHandle* fileHandle = PlatformFile.OpenWrite(pathname);
	FArchiveFileWriterGeneric archive(fileHandle, pathname, 0);
	bool success = FImageUtils::ExportRenderTarget2DAsPNG(texture, archive);
	UE_LOG(LogTemp, Warning, TEXT("Save success: %s"), success ? TEXT("Success") : TEXT("Error"));
}
