// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Engine/DamageEvents.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = GunRootComponent;

	MuzzlePos = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzlePosition"));
	GunRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	MuzzlePos->SetupAttachment(GunRootComponent);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::HandleOnWeaponFired()
{
	OnWeaponFired.ExecuteIfBound();
}

void AWeaponBase::ShootRaycast(FVector direction, float range)
{
	//Set up Variables
	FHitResult hitResult;
	FCollisionQueryParams CollisionParameters;

	FVector Start = MuzzlePos->GetComponentLocation();
	FVector End = ((direction * range) + Start);
	//DebugLine
	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5, 0, 1);

	//Perform Raycast and apply damage
	if (GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECC_WorldDynamic, CollisionParameters))
	{
		//GLog->Log(hitResult.GetActor()->GetFullName());
		FDamageEvent DamageEvent;
		if (hitResult.GetActor() != nullptr)
		{
			hitResult.GetActor()->TakeDamage(10, OUT DamageEvent, nullptr, this);
		}
	}
}

void AWeaponBase::CalculateRecoil(FRecoilImpulseData& recoilDataOutput)
{
	FVector positionImpulse;

	FRotator rotationImpulse;

	positionImpulse.Z = FMath::RandRange(WeaponRecoilData.WeaponPositionRiseRecoilRange.X, WeaponRecoilData.WeaponPositionRiseRecoilRange.Y);
	rotationImpulse.Pitch = FMath::RandRange(WeaponRecoilData.WeaponRotationRiseRecoilRange.X, WeaponRecoilData.WeaponRotationRiseRecoilRange.Y);
	rotationImpulse.Yaw = FMath::RandRange(WeaponRecoilData.WeaponRotationHorizontalRecoilRange.X, WeaponRecoilData.WeaponRotationHorizontalRecoilRange.Y);

	recoilDataOutput.PositionRecoilImpulse = positionImpulse;
	recoilDataOutput.RotationRecoilImpulse = rotationImpulse;
}

float AWeaponBase::GetAimSpeed()
{
	return AimSpeed;
}

FWeaponOffset AWeaponBase::GetOffsetData()
{
	return WeaponOffsetData;
}
