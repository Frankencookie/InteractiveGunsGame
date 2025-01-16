// Fill out your copyright notice in the Description page of Project Settings.


#include "CylinderMagazineComponent.h"

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

	if (Index > BulletCount)
	{
		Index = 0;
	}
}
