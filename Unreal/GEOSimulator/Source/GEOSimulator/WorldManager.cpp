// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldManager.h"
#include "Engine/World.h"
#include "GameFrameWork/PlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "MapChunk.h"
#include "Misc/FileHelper.h"

// Sets default values
AWorldManager::AWorldManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldManager::BeginPlay()
{
	Super::BeginPlay();
    
    LoadFile(FPaths::ProjectDir() + "Maps/example9x9big/", "pallars15.json");
	
	//LoadExample9x9();

	/*FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	FTransform transform;

	AMapChunk* chunk1 = GetWorld()->SpawnActorDeferred<AMapChunk>(AMapChunk::StaticClass(), transform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	UE_LOG(LogTemp, Warning, TEXT("SetTexturesAndMesh"));
	chunk1->AddTexture("RGB", FPaths::ProjectDir() + "Maps/outputwms.jpg");
	chunk1->AddTexture("IR", FPaths::ProjectDir() + "Maps/outputwmsi.jpg");
	//chunk1->AddTexture("B02", FPaths::ProjectDir() + "Maps/outputwmsb02.jpg");
	chunk1->SetMeshFile(FPaths::ProjectDir() + "Maps/outputwcs.obj");
	chunk1->FinishSpawning(transform);

	chunks.Add(chunk1);

	FVector Location2(1250.0f, 0.0f, 0.0f);

	transform.SetLocation(Location2);
	AMapChunk* chunk2 = GetWorld()->SpawnActorDeferred<AMapChunk>(AMapChunk::StaticClass(), transform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	UE_LOG(LogTemp, Warning, TEXT("SetTexturesAndMesh"));
	chunk2->AddTexture("RGB", FPaths::ProjectDir() + "Maps/outputwms2.jpg");
	chunk2->AddTexture("IR", FPaths::ProjectDir() + "Maps/outputwmsi2.jpg");
	chunk2->SetMeshFile(FPaths::ProjectDir() + "Maps/outputwcs2.obj");
	chunk2->FinishSpawning(transform);

	chunks.Add(chunk2);*/
	
}

void AWorldManager::LoadFile(FString path, FString fileName)
{
    FString JsonFilePath;
    JsonFilePath.Append(path);
    JsonFilePath.Append(fileName);
    FString JsonString; //Json converted to FString
    
    FFileHelper::LoadFileToString(JsonString,*JsonFilePath);
    
    UE_LOG(LogTemp, Warning, TEXT("Path [%s] fileName [%s] fullPath [%s]"), *path, *fileName, *JsonFilePath);
    
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
    
    TArray<TSharedPtr<FJsonValue>> JsonItems;
    
    if (FJsonSerializer::Deserialize(JsonReader, JsonItems) && JsonObject.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("N Elements %d"), JsonItems.Num());
        for(int i = 0; i < JsonItems.Num(); i++)
        {
            TSharedPtr<FJsonValue> Item = JsonItems[i];
            TSharedPtr<FJsonObject> jsonObject = Item.Get()->AsObject();
            
            //Load a chunk
            FJsonObject* obj = jsonObject.Get();
            FString fileName = path+obj->GetStringField("file");
            double x = obj->GetNumberField("x");
            double y = obj->GetNumberField("y");
            
            //Set te origin of data
            if(i == 0)
                originVector = FVector(x, -y, 0.f);
            
            //Create chunk
            FTransform transform;
            FVector location = FVector(x, -y, 0.f) - originVector;
            
            transform.SetLocation(location);
            AMapChunk* chunk = GetWorld()->SpawnActorDeferred<AMapChunk>(AMapChunk::StaticClass(), transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
            
            
//          chunk00->AddTexture("RGB", FPaths::ProjectDir() + "Maps/example9x9/outputwms00.jpg");
//          chunk00->AddTexture("IR", FPaths::ProjectDir() + "Maps/example9x9/outputwmsi00.jpg");
            
            
            TArray<TSharedPtr<FJsonValue>> texturesItems = obj->GetArrayField("textures");
            for(int j = 0; j < texturesItems.Num(); j++)
            {
                TSharedPtr<FJsonValue> txtValue = texturesItems[j];
                TSharedPtr<FJsonObject> txtPtrObj = txtValue.Get()->AsObject();
                FJsonObject* txtObj = txtPtrObj.Get();
                
                FString txtName = txtObj->GetStringField("name");
                FString txtFile = path+txtObj->GetStringField("file");
                
                UE_LOG(LogTemp, Warning, TEXT("Texture Name[%s] File[%s]"), *txtName, *txtFile);
                chunk->AddTexture(FName(*txtName), txtFile);
            }
            
            chunk->SetMeshFile(fileName);
            chunk->FinishSpawning(transform);
            chunks.Add(chunk);
            UE_LOG(LogTemp, Warning, TEXT("File N[%d] File[%s]"), i, *fileName);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Problem desearialize JSON"));
    }
}

// Called every frame
void AWorldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<AMapChunk*> AWorldManager::GetChunks()
{
	return chunks;
}

void AWorldManager::ChangeTexture()
{
	NextTexture(textureSelected);
	UE_LOG(LogTemp, Warning, TEXT("NewTexture %d"), textureSelected);

	for (int i = 0; i < chunks.Num(); i++)
	{
		chunks[i]->ChangeTexture(textureSelected);
	}
}

void AWorldManager::NextTexture(TextureSelected& textureActual)
{
	switch (textureActual)
	{
	case RGB:
		textureActual = IR;
		break;
	case IR:
		textureActual = B01;
		break;
	case B01:
		textureActual = B02;
		break;
	case B02:
		textureActual = RGB;
		break;
	}
}
