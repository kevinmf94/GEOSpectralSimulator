#pragma once

#include "CoreMinimal.h"
#include "PixelFormat.h"
#include "Engine/Texture2D.h"
#include "ImageLoader.generated.h"


/**
Utility class for asynchronously loading an image into a texture.
Allows Blueprint scripts to request asynchronous loading of an image and be notified when loading is complete.
*/
UCLASS()
class GEOSIMULATOR_API UImageLoader : public UObject
{
	GENERATED_BODY()
public:
	static UTexture2D* LoadImageFromDisk(UObject* Outer, const FString& ImagePath);

private:
	/** Helper function to dynamically create a new texture from raw pixel data. */
	static UTexture2D* CreateTexture(UObject* Outer, const TArray<uint8>& PixelData, int32 InSizeX, int32 InSizeY, EPixelFormat PixelFormat = EPixelFormat::PF_B8G8R8A8, FName BaseName = NAME_None);
};