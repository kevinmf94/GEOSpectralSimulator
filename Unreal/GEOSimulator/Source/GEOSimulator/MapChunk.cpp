// Fill out your copyright notice in the Description page of Project Settings.

#include "MapChunk.h"

//Read files and manipulate strings
#include "Misc/FileHelper.h"
#include "Public/Containers/UnrealString.h"
#include "ImageLoader.h"

//Material
#include "Classes/Materials/Material.h"
#include "Classes/Materials/MaterialInstanceDynamic.h"

//Load mesh
#include "UObject/ConstructorHelpers.h"
#include "ProceduralMeshComponent.h"

//Keys
#include "Classes/InputCoreTypes.h"
#include "Framework/Commands/InputChord.h"
#include "Components/InputComponent.h"

// Sets default values
AMapChunk::AMapChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = mesh;

	ConstructorHelpers::FObjectFinder<UMaterial> matFind(TEXT("/Game/Terrain/MapTexture.MapTexture"));
	if (matFind.Succeeded())
	{
		material = matFind.Object;
	}

	#if WITH_EDITOR
//        this->AddTexture("RGB", FPaths::ProjectDir() + "Maps/outputwms.jpg");
//        this->AddTexture("IR", FPaths::ProjectDir() + "Maps/outputwmsi.jpg");
//        this->SetMeshFile(FPaths::ProjectDir() + "Maps/outputwcs.obj");
	#endif
}

void AMapChunk::PostActorCreated()
{
	Super::PostActorCreated();

	#if WITH_EDITOR
		/*LoadMeshFile();
		UE_LOG(LogTemp, Warning, TEXT("SetActorRotation"));
		if (!SetActorRotation(FRotator(0.f, 90.f, 0.f)))
		{
			UE_LOG(LogTemp, Warning, TEXT("Error SetActorRotation"));
		}

		materialDynamic = UMaterialInstanceDynamic::Create(material, this);
		LoadTexture();
		mesh->SetMaterial(0, materialDynamic);*/
	#endif
}

// Called when the game starts or when spawned
void AMapChunk::BeginPlay()
{
    Super::BeginPlay();
    
    LoadMeshFile();
    
    if (!SetActorRotation(FRotator(0.f, 90.f, 0.f)))
    {
        UE_LOG(LogTemp, Warning, TEXT("Error SetActorRotation in AMapChunk"));
    }
    
    materialDynamic = UMaterialInstanceDynamic::Create(material, this);
    LoadTextures();
    mesh->SetMaterial(0, materialDynamic);
}

// Called every frame
void AMapChunk::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

void AMapChunk::LoadTextures()
{
	for (auto& Elem : texturesFiles)
	{
		UTexture2D* texture = UImageLoader::LoadImageFromDisk(this, *Elem.Value);
		if (texture != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("TextureLoaded"));
            textureMap.Add(Elem.Key, texture);
		} else 
		{
			UE_LOG(LogTemp, Warning, TEXT("TextureProblem %s"), *(Elem.Key.ToString()));
		}
	}
	
    TArray<FName> texturesKeys;
    TArray<UTexture2D*> texturesValues;
    textureMap.GenerateKeyArray(texturesKeys);
    textureMap.GenerateValueArray(texturesValues);
    
    materialDynamic->SetTextureParameterValue("Texture", texturesValues[0]);
    textureSelected = texturesKeys[0];
}

void AMapChunk::ChangeTexture(FName textureName)
{
	UTexture2D** value = textureMap.Find(textureName);
	if(value != nullptr)
	{
		if(*value != nullptr)
			materialDynamic->SetTextureParameterValue("Texture", *value);
		else
			UE_LOG(LogTemp, Warning, TEXT("TextureProblem change %s"), *(textureName.ToString()));
	} 
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("TextureProblem change2 %s"), *(textureName.ToString()));
	}
}

void AMapChunk::PostLoad()
{
	Super::PostLoad();
	//CreateTriangle();
	//LoadMeshFile();
	//LoadTexture();
	UE_LOG(LogTemp, Warning, TEXT("AMapChunk::PostLoad"));
	
}

void AMapChunk::LoadMeshFile()
{
	TArray<FVector> vertices;
	TArray<int32> Triangles;
	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> tangents;
	TArray<FLinearColor> vertexColors;

	TArray<FString> fileItems;
	bool success = FFileHelper::LoadFileToStringArray(fileItems, *meshFile);
	if (success)
	{
		UE_LOG(LogTemp, Warning, TEXT("FirstLine %s"), *(fileItems[0]));
		UE_LOG(LogTemp, Warning, TEXT("File Open NLines = %d"), fileItems.Num());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Error load mesh"));
	}

	UE_LOG(LogTemp, Warning, TEXT("Path %s"), *meshFile);

	for (int i = 0; i < fileItems.Num(); i++)
	{
		if (fileItems[i].Contains(TEXT("vn"), ESearchCase::CaseSensitive))
		{
			TArray<FString> vnLine;
			fileItems[i].ParseIntoArray(vnLine, TEXT(" "));
			if (vnLine.Num() == 4)
			{
				float x = FCString::Atof(*vnLine[1]);
				float y = FCString::Atof(*vnLine[2]);
				float z = FCString::Atof(*vnLine[3]);
				normals.Add(FVector(x, y, z));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Error Line %d Str [%s] Num items %d"), i, *fileItems[i], vnLine.Num());
				break;
			}
		}
		else if (fileItems[i].Contains(TEXT("vt"), ESearchCase::CaseSensitive))
		{
			TArray<FString> vtLine;
			fileItems[i].ParseIntoArray(vtLine, TEXT(" "));
			if (vtLine.Num() == 3)
			{
				float x = FCString::Atof(*vtLine[1]);
				float y = FCString::Atof(*vtLine[2]);
				UV0.Add(FVector2D(x, y));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Error Line %d Str [%s] Num items %d"), i, *fileItems[i], vtLine.Num());
				break;
			}
		}
		else if ( fileItems[i].Contains(TEXT("v"), ESearchCase::CaseSensitive) )
		{
			TArray<FString> vLine;
			int32 count = 0;
			fileItems[i].ParseIntoArray(vLine, TEXT(" "));
			if (vLine.Num() == 4)
			{
				float x = FCString::Atof(*vLine[1]);
				float y = FCString::Atof(*vLine[2]);
				float z = FCString::Atof(*vLine[3]);
				vertices.Add(FVector(x, -y, z));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Error Line %d Str [%s] Num items %d"), i, *fileItems[i], vLine.Num());
				break;
			}
		}
		else if (fileItems[i].Contains(TEXT("f"), ESearchCase::CaseSensitive))
		{
			TArray<FString> fLine;
			TArray<FString> fItem;
			fileItems[i].ParseIntoArray(fLine, TEXT(" "));
            
            #if PLATFORM_WINDOWS
            int j = 0;
            #elif PLATFORM_MAC
            int j = 1;
            #elif PLATFORM_LINUX
            int j = 1;
            #endif
            
			for (; j < fLine.Num(); j++)
			{
				fLine[j].ParseIntoArray(fItem, TEXT("/"));
				int32 faceId = FCString::Atoi(*fItem[0]);
				Triangles.Add(faceId - 1);
			}
		}
	}

	mesh->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, false);

	// Enable collision data
	mesh->ContainsPhysicsTriMeshData(false);
}

void AMapChunk::AddTexture(FName param, FString pathfile)
{
	texturesFiles.Add(param, pathfile);
}

void AMapChunk::SetMeshFile(FString pathfile)
{
	meshFile = pathfile;
}

TArray<FName> AMapChunk::GetTexturesNames()
{
    TArray<FName> keys;
    textureMap.GenerateKeyArray(keys);
    return keys;
}
