// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WeaponData/WeaponDataStructs.h"
#include "Bullet.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class INTERACTIVEGUNS_API UBullet : public UObject
{
	GENERATED_BODY()
	
public:
	FBulletRecoilData RecoilData;

	bool Fired;
};
