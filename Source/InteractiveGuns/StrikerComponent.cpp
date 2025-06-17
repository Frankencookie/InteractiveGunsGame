// Fill out your copyright notice in the Description page of Project Settings.


#include "StrikerComponent.h"
#include "Kismet/GameplayStatics.h"

UStrikerComponent::UStrikerComponent()
{
	Cocking = false;
	Cocked = false;
	UnCocked = true;
	LerpValue = 0;
}

void UStrikerComponent::BeginPlay()
{
	Super::BeginPlay();

	UncockedPosition = GetRelativeLocation();
	UncockedRotation = GetRelativeRotation();
}

void UStrikerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Cocking && !Cocked)
	{
		UnCocked = false;
		LerpValue += DeltaTime / CockTime;

		if (LerpValue > 0.9)
		{
			LerpValue = 1;

			Cocked = true;
		}

	}
	else if (!Cocking && !UnCocked)
	{
		LerpValue -= DeltaTime / CockTime;

		if (LerpValue < 0)
		{
			LerpValue = 0;
		}
	}

	SetRelativeLocation(FMath::Lerp(UncockedPosition, UncockedPosition + CockedPosition, LerpValue));
	SetRelativeRotation(FMath::Lerp(UncockedRotation, UncockedRotation + CockedRotation, LerpValue));
}

void UStrikerComponent::OnRegister()
{
	Super::OnRegister();
	PrimaryComponentTick.bCanEverTick = true;
}

void UStrikerComponent::CockStriker()
{
	Cocking = true;
}

void UStrikerComponent::UncockStriker()
{
	Cocking = false;
}

bool UStrikerComponent::StrikeStriker()
{
	if (!Cocked)
	{
		return false;
	}
	Cocking = false;
	Cocked = false;
	UnCocked = true;
	LerpValue = 0;

	SetRelativeLocation(UncockedPosition);
	SetRelativeRotation(UncockedRotation);

	if (StrikeSound != nullptr)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), StrikeSound, GetComponentLocation());

	return true;
}
