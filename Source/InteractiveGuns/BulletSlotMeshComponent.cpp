// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletSlotMeshComponent.h"
#include "WorldBullet.h"

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
	bInserting = IsInserting;
	bAnimating = true;
	AnimationProgress = 0;

	SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AnimationStartPos = StartPos;
	AnimationEndPos = EndPos;
}

void UBulletSlotMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bAnimating)
		return;

	AnimationProgress += DeltaTime * AnimationSpeed;

	if (AnimationProgress > 1.0f)
	{
		bAnimating = false;

		SetRelativeLocation(InsertedPosition);

		SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		SetVisibility(bInserting);

		if (!bInserting && bFired && WorldBulletType != nullptr)
		{
			AWorldBullet* NewWorldBullet = GetWorld()->SpawnActor<AWorldBullet>(WorldBulletType);

			NewWorldBullet->Initialise(GetStaticMesh(), true);

			FVector worldOffsetPosition = GetComponentLocation();
			//FVector localOffsetDelta = RemovedRelativePosition - worldOffsetPosition;
			//worldOffsetPosition += GetForwardVector() * localOffsetDelta.X;
			//worldOffsetPosition += GetRightVector() * localOffsetDelta.Y;
			//worldOffsetPosition += GetUpVector() * localOffsetDelta.Z;

			worldOffsetPosition += GetForwardVector() * RemovedRelativePosition.X;

			NewWorldBullet->SetActorLocationAndRotation(worldOffsetPosition, GetComponentRotation());
		}

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
	SetFired(false);

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

void UBulletSlotMeshComponent::SetFired(bool value)
{
	SetScalarParameterValueOnMaterials("Fired", value ? 1 : 0);
	bFired = value;
}
