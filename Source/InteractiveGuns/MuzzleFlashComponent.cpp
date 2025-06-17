// Fill out your copyright notice in the Description page of Project Settings.


#include "MuzzleFlashComponent.h"

UMuzzleFlashComponent::UMuzzleFlashComponent()
{
	SetIntensity(0);
	SetIntensityUnits(ELightUnits::Candelas);

	bUseTemperature = true;
	Temperature = 4400;
	AttenuationRadius = 400;
}

void UMuzzleFlashComponent::OnRegister()
{
	Super::OnRegister();
	PrimaryComponentTick.bCanEverTick = true;
}

void UMuzzleFlashComponent::DoMuzzleFlash()
{
	Active = true;
	bAffectsWorld = true;
	CurrentValue = 0;
}

void UMuzzleFlashComponent::DeactivateFlash()
{
	Active = false;
	bAffectsWorld = false;
}

void UMuzzleFlashComponent::BeginPlay()
{
	Super::BeginPlay();
	DeactivateFlash();
}

void UMuzzleFlashComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!Active)
		return;

	if (CurrentValue > duration)
	{
		DeactivateFlash();
		return;
	}

	SetIntensity(MuzzleFlashCurve->FloatCurve.Eval(CurrentValue) * MaximumBrightness);

	CurrentValue += DeltaTime;
}