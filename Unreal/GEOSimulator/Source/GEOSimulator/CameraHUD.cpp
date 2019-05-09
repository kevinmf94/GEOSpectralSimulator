// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraHUD.h"

void ACameraHUD::BeginPlay()
{
	Super::BeginPlay();
}

void ACameraHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ACameraHUD::DrawHUD()
{
	if (texture)
	{
		DrawTexture(texture, 100.f, 100.f, 200.f, 200.f, 0.f, 0.f, 1.f, 1.f);
	}
		
}

void ACameraHUD::SetTexture(UTexture* texture)
{
	this->texture = texture;
}