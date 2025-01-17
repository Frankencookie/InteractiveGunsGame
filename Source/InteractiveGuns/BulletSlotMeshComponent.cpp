// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletSlotMeshComponent.h"

void UBulletSlotMeshComponent::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate delegate;

	delegate.BindUFunction(this, "OnBulletClickHandler");

	OnClicked.Add(delegate);

}

void UBulletSlotMeshComponent::OnBulletClickHandler()
{
	OnBulletClicked.Broadcast(Index);
}
