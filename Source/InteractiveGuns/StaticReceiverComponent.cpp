// Fill out your copyright notice in the Description page of Project Settings.

#include "StaticReceiverComponent.h"
#include "MagazineComponentBase.h"

bool UStaticReceiverComponent::HammerStruck(UMagazineComponentBase* currentMagazine)
{
	if (currentMagazine == nullptr)
	{
		return false; //Magazine was not present, do nothing
	}
	if (currentMagazine->MagazineRemoved)
	{
		return false; //Magazine was not present, do nothing
	}

	UBullet* bullet = currentMagazine->GetNextBullet();

	if (bullet == nullptr)
	{
		return false;
	}

	return bullet->TryFire();
}
