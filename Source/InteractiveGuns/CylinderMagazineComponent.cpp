// Fill out your copyright notice in the Description page of Project Settings.


#include "CylinderMagazineComponent.h"
#include "BulletSlotMeshComponent.h"

void UCylinderMagazineComponent::BeginPlay()
{
	Super::BeginPlay();
}

UBullet* UCylinderMagazineComponent::GetBulletAtIndex(int index)
{
	if (index > bullets.Num() - 1)
	{
		GLog->Log(ELogVerbosity::Error, "Tried to access a bullet from invalid magazine index");
		return nullptr;
	}

	return bullets[index];
}

UBullet* UCylinderMagazineComponent::GetNextBullet()
{
	return GetBulletAtIndex(Index);
}

bool UCylinderMagazineComponent::InsertBulletAtIndex(UBullet* bullet, int index)
{
	return false;
}

void UCylinderMagazineComponent::IncrementCylinderIndex()
{
	Index++;

	if (Index > MagazineSize - 1)
	{
		Index = 0;
	}
}

void UCylinderMagazineComponent::UnloadBulletAtIndex(int index)
{
	if (index > bullets.Num() - 1)
	{
		GLog->Log(ELogVerbosity::Error, "Tried to remove a bullet from invalid magazine index");
		return;
	}

	bullets[index] = nullptr;
}

void UCylinderMagazineComponent::HandleBulletClicked(int index)
{
	if (index > bullets.Num() - 1)
	{
		GLog->Log(ELogVerbosity::Error, "Trying to handle a bullet using invalid index");
		return;
	}

	UBullet* bullet = bullets[index];

	bullet->Loaded = !bullet->Loaded;

	if (bullet->Loaded)
		bullet->Fired = false;

	bulletSlots[index]->SetVisibility(bullet->Loaded);
}

void UCylinderMagazineComponent::HandleEjectorClicked()
{
	for (int i = 0; i < bullets.Num(); i++)
	{
		bullets[i]->Loaded = false;
		bulletSlots[i]->SetVisibility(false);
	}
}
