// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletSlotMeshComponent.h"

void UBulletSlotMeshComponent::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate delegate;

	delegate.BindUFunction(this, "OnBulletClickHandler");

	OnClicked.Add(delegate);

	InsertedPosition = GetRelativeLocation();
}

void UBulletSlotMeshComponent::SetAnimationData(FVector StartPos, FVector EndPos, bool IsInserting)
{
	SetVisibility(true);
	Inserting = IsInserting;
	Animating = true;
	AnimationProgress = 0;

	SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AnimationStartPos = StartPos;
	AnimationEndPos = EndPos;
}

void UBulletSlotMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Animating)
		return;

	AnimationProgress += DeltaTime * AnimationSpeed;

	if (AnimationProgress > 1.0f)
	{
		Animating = false;

		SetRelativeLocation(InsertedPosition);

		SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		SetVisibility(Inserting);

		return;
	}

	SetRelativeLocation(FMath::Lerp(AnimationStartPos, AnimationEndPos, AnimationProgress));
}

void UBulletSlotMeshComponent::OnRegister()
{
	Super::OnRegister();
	PrimaryComponentTick.bCanEverTick = true;
}

void UBulletSlotMeshComponent::OnBulletClickHandler()
{
	OnBulletClicked.Broadcast(Index);
}

void UBulletSlotMeshComponent::InsertBullet()
{
	SetScalarParameterValueOnMaterials("Fired", 0);

	SetAnimationData(RemovedRelativePosition, InsertedPosition, true);
}

void UBulletSlotMeshComponent::RemoveBullet()
{
	SetAnimationData(InsertedPosition, RemovedRelativePosition, false);
}

void UBulletSlotMeshComponent::SetIndex(int value)
{
	Index = value;
}
