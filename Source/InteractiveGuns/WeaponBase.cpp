// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Engine/DamageEvents.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MuzzlePos = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzlePosition"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	MuzzlePos->SetupAttachment(RootComponent);
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
		GLog->Log(hitResult.GetActor()->GetFullName());
		FDamageEvent DamageEvent;
		if (hitResult.GetActor() != nullptr)
		{
			hitResult.GetActor()->TakeDamage(10, OUT DamageEvent, nullptr, this);
		}
	}
}

FVector AWeaponBase::GetOffset(bool aiming)
{
	if (aiming)
	{
		return AimingOffsetFromWielder;
	}
	else
	{
		return OffsetFromWielder;
	}
	
}

FVector AWeaponBase::GetManipulateModeOffset()
{
	return ManipulateModeOffsetFromWielder;
}

float AWeaponBase::GetAimSpeed()
{
	return AimSpeed;
}

FRotator AWeaponBase::GetManipulateModeRotation()
{
	return ManipulateModeRotation;
}
