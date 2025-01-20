// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"


bool UBullet::TryFire()
{
	if(!Loaded || Fired)
		return false;

	Fired = true;

	return true;
}

void UBullet::SetVisualComponent(UBulletSlotMeshComponent* component)
{
	VisualComponent = component;
}

UBulletSlotMeshComponent* UBullet::GetVisualComponent()
{
	return VisualComponent;
}
