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
    
    //Example big terrain preloaded
    //worldOrigin = FVector(326737.05928061914f, -4676971.31928062f, 0.f);
}

void AWorldManager::LoadFile(FString path, FString fileName)
{
    FVector correction(-150.f, 150.f, 0.f);
    
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
            
            //Load chunk pos and set correction
            TSharedPtr<FJsonObject> chunkPtrObj = jsonObject->GetObjectField("chunkpos");
            FJsonObject* chunkObj = chunkPtrObj.Get();
            FVector correctionChunk = correction;
            
            double chunkX = chunkObj->GetNumberField("x");
            double chunkY = chunkObj->GetNumberField("y");
            
            //correctionChunk.X = correctionChunk.X*chunkX;
//            correctionChunk.Y = correctionChunk.Y*chunkY;
            
            //Get cellsize, sizeofxy and calculate the origin
            if(i == 0) {
                TSharedPtr<FJsonObject> sizePtrObj = jsonObject->GetObjectField("size");
                FJsonObject* sizeObj = sizePtrObj.Get();
                
                double sizeY = sizeObj->GetNumberField("y");
                double cellsize =  jsonObject->GetNumberField("cellsize");
                
                worldOrigin = FVector(x, -y+(sizeY*cellsize), 0.f);
                UE_LOG(LogTemp, Warning, TEXT("Calculated WorldOrigin %f %f"), worldOrigin.X, worldOrigin.Y)
            }
            
            //Create chunk
            FTransform transform;
            FVector location = FVector(x, -y, 0.f) - worldOrigin;
            
//            if(i != 0)
//                location = location+correctionChunk;
            
            transform.SetLocation(location);
            AMapChunk* chunk = GetWorld()->SpawnActorDeferred<AMapChunk>(AMapChunk::StaticClass(), transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
            
            
            //Load textures
            TArray<TSharedPtr<FJsonValue>> texturesItems = obj->GetArrayField("textures");
            for(int j = 0; j < texturesItems.Num(); j++)
            {
                TSharedPtr<FJsonValue> txtValue = texturesItems[j];
                TSharedPtr<FJsonObject> txtPtrObj = txtValue.Get()->AsObject();
                FJsonObject* txtObj = txtPtrObj.Get();
                
                FString txtName = txtObj->GetStringField("name");
                FString txtFile = path+txtObj->GetStringField("file");
                
                chunk->AddTexture(FName(*txtName), txtFile);
            }
            
            //Finish spawn chunk
            chunk->SetMeshFile(fileName);
            chunk->FinishSpawning(transform);
            chunks.Add(chunk);
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

FVector AWorldManager::GetWorldOrigin()
{
    return worldOrigin;
}
