// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldManager.h"
#include "Engine/World.h"
#include "GameFrameWork/PlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "MapChunk.h"
#include "Misc/FileHelper.h"
#include "Misc/Parse.h"

// Sets default values
AWorldManager::AWorldManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    //string
    if (FParse::Value(FCommandLine::Get(), TEXT("-folderMap"), folderMap)) {
        folderMap = folderMap.Replace(TEXT("="), TEXT(""));
    }
    
    if (FParse::Value(FCommandLine::Get(), TEXT("-map"), map)) {
        map = map.Replace(TEXT("="), TEXT(""));
    }
}

// Called when the game starts or when spawned
void AWorldManager::BeginPlay()
{
	Super::BeginPlay();
    
    //LoadFile(FPaths::ProjectDir() + "Maps/example9x9big/", "pallars15.json");
    #if WITH_EDITOR
        LoadFile(FPaths::ProjectDir() + folderMap, map);
    #else
        LoadFile(FPaths::LaunchDir() + folderMap, map);
    #endif
    
    //LoadFile(FPaths::ProjectDir() + folderMap, map);
    
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
    UE_LOG(LogTemp, Warning, TEXT("JsonString [%s]"), *JsonString);
    
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
            
            correctionChunk.X = correctionChunk.X*chunkX;
            correctionChunk.Y = correctionChunk.Y*chunkY;
            
            //Get cellsize, sizeofxy and calculate the origin
            if(i == 0) {
                TSharedPtr<FJsonObject> sizePtrObj = jsonObject->GetObjectField("size");
                FJsonObject* sizeObj = sizePtrObj.Get();
                
                double sizeY = sizeObj->GetNumberField("y");
                double cellsize =  jsonObject->GetNumberField("cellsize");
                
                UE_LOG(LogTemp, Warning, TEXT("Calculated Calc params %f %f %f"), y, sizeY, cellsize)
                worldOrigin = FVector(x, y-(sizeY*cellsize), 0.f);
                UE_LOG(LogTemp, Warning, TEXT("Calculated WorldOrigin %f %f"), worldOrigin.X, worldOrigin.Y)
            }
            
            //Create chunk
            FTransform transform;
            FVector location = WorldToUnreal(FVector(x, y, 0.f));
            
            if(i != 0)
                location = location+correctionChunk;
            
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
                textures.AddUnique(FName(*txtName));
            }
            
            //Finish spawn chunk
            chunk->SetMeshFile(fileName);
            chunk->FinishSpawning(transform);
            chunks.Add(chunk);
        }
        
        //Check the valid textures
        TArray<FName> invalids;
        for(int i = 0; i < textures.Num(); i++)
        {
            if(!IsValidTexture(textures[i]))
                invalids.AddUnique(textures[i]);
        }
        
        for(int i = 0; i < invalids.Num(); i++)
        {
            textures.Remove(invalids[i]);
        }
        
        textureSelected = textures[0];
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

/* Change texture used by the event of player */
void AWorldManager::ChangeTexture()
{
    textureSelected = NextTexture();
	UE_LOG(LogTemp, Warning, TEXT("NewTexture %s"), *textureSelected.ToString());

	for (int i = 0; i < chunks.Num(); i++)
	{
		chunks[i]->ChangeTexture(textureSelected);
	}
}

/* Used to set a specify texture saved in textureSelected variable */
void AWorldManager::ChangeTexture(FName newTexture)
{
    textureSelected = newTexture;
	UE_LOG(LogTemp, Warning, TEXT("ChangeTexture2 NewTexture %s"), *textureSelected.ToString());

	for (int i = 0; i < chunks.Num(); i++)
	{
		chunks[i]->ChangeTexture(textureSelected);
	}
}

FName AWorldManager::NextTexture()
{
    int32 pos;
    FName next;
    
    pos = textures.Find(textureSelected);
    if(pos+1 >= textures.Num())
        return textures[0];
    
    return textures[pos+1];
}

bool AWorldManager::IsValidTexture(FName textureName)
{
    bool valid = true;
    int tmpIndex;

    //Shaders
    if(IsShader(textureName))
        return true;
    
    for (int i = 0; i < chunks.Num(); i++)
    {
        TArray<FName> textures = chunks[i]->GetTexturesNames();
        valid = textures.Find(textureName, tmpIndex);
    }
    
    return valid;
}

bool AWorldManager::IsShader(FName textureName)
{
    //Shaders
    if(FName("depth") == textureName)
        return true;

    return false;
}

FName AWorldManager::GetTextureSelected()
{
    return textureSelected;
}

FVector AWorldManager::GetWorldOrigin()
{
    return worldOrigin;
}

FVector AWorldManager::WorldToUnreal(FVector vector)
{
    vector = vector-worldOrigin;
    vector.Y = -vector.Y;
    return vector;
}

FVector AWorldManager::UnrealToWorld(FVector vector)
{
    FVector worldOriginT = worldOrigin;
    vector.Y = -vector.Y;
    vector = vector+worldOriginT;
    return vector;
}
