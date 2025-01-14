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


/**
 * 
 */
UCLASS()
class INTERACTIVEGUNS_API UWeaponDataStructs : public UObject
{
	GENERATED_BODY()
	
};
