// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "BulletSlotMeshComponent.h"


bool UBullet::TryFire()
{
	if(!Loaded || Fired)
		return false;

	Fired = true;

	if(VisualComponent != nullptr)
		VisualComponent->SetFired(true);

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
