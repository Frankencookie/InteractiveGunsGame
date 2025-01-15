// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WeaponDataStructs.generated.h"


USTRUCT(BlueprintType)
struct FWeaponOffset
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FVector OffsetFromWielder;

	UPROPERTY(EditAnywhere)
	FVector AimingOffsetFromWielder;

	UPROPERTY(EditAnywhere)
	FVector ManipulateModeOffsetFromWielder;

	UPROPERTY(EditAnywhere)
	FRotator ManipulateModeRotation;
};

USTRUCT(BlueprintType)
struct FWeaponRecoilData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FVector2D WeaponPositionRiseRecoilRange;

	UPROPERTY(EditAnywhere)
	FVector2D WeaponRotationRiseRecoilRange;

	UPROPERTY(EditAnywhere)
	FVector2D WeaponRotationHorizontalRecoilRange;
};

USTRUCT(BlueprintType)
struct FBulletRecoilData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	float RecoilMultiplier = 1;
};

USTRUCT(BlueprintType)
struct FRecoilImpulseData
{
	GENERATED_USTRUCT_BODY()

	FVector PositionRecoilImpulse;
	FRotator RotationRecoilImpulse;
};


/**
 * 
 */
UCLASS()
class INTERACTIVEGUNS_API UWeaponDataStructs : public UObject
{
	GENERATED_BODY()
	
};
