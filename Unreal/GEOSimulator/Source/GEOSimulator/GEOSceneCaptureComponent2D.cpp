// Fill out your copyright notice in the Description page of Project Settings.


#include "GEOSceneCaptureComponent2D.h"
#include "GEOSimulatorAPIGameModeBase.h"
#include "Engine/World.h"

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