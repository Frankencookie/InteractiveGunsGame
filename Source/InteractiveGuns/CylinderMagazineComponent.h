// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagazineComponentBase.h"
#include "CylinderMagazineComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INTERACTIVEGUNS_API UCylinderMagazineComponent : public UMagazineComponentBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	UBullet* GetBulletAtIndex(int index);

	UFUNCTION(BlueprintCallable)
	UBullet* GetNextBullet();

	UFUNCTION(BlueprintCallable)
	bool InsertBulletAtIndex(UBullet* bullet, int index);

	UFUNCTION(BlueprintCallable)
	void IncrementCylinderIndex();

	int Index;
};
