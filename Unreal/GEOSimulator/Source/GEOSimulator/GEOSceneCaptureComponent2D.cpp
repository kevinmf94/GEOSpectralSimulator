// Fill out your copyright notice in the Description page of Project Settings.

#include "GEOSceneCaptureComponent2D.h"

#include "GEOSimulatorAPIGameModeBase.h"
#include "Engine/TextureRenderTarget2D.h"

UGEOSceneCaptureComponent2D::UGEOSceneCaptureComponent2D()
{
	texture = NewObject<UTextureRenderTarget2D>();
	texture->InitCustomFormat(1000, 1000, PF_B8G8R8A8, false);
	this->TextureTarget = texture;
}

void UGEOSceneCaptureComponent2D::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	/*AGEOSimulatorAPIGameModeBase* gameMode = GetWorld()->GetAuthGameMode<AGEOSimulatorAPIGameModeBase>();
	AWorldManager* manager = gameMode->GetWorldManager();
	manager->ChangeTextures();

	if (bCaptureEveryFrame)
	{
		CaptureScene();
	}


	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	manager->ChangeTextures();*/
}

UTextureRenderTarget2D* UGEOSceneCaptureComponent2D::GetTexture()
{
	return texture;
}