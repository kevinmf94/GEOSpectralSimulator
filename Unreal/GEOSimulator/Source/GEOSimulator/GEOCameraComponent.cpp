// Fill out your copyright notice in the Description page of Project Settings.


#include "GEOCameraComponent.h"
#include "GEOSceneCaptureComponent2D.h"

UGEOCameraComponent::UGEOCameraComponent()
{
	FString name = this->GetName();
	name = name.Append("SceneCapture");

	sceneCapture = CreateDefaultSubobject<UGEOSceneCaptureComponent2D>(*name);
	sceneCapture->ProjectionType = ECameraProjectionMode::Perspective;
	sceneCapture->CaptureSource = ESceneCaptureSource::SCS_SceneColorSceneDepth;

	sceneCapture->SetupAttachment(this);
}

UGEOSceneCaptureComponent2D* UGEOCameraComponent::GetSceneCapture()
{
	return sceneCapture;
}