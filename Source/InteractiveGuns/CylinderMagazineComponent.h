// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagazineComponentBase.h"
#include "CylinderMagazineComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (GunComponents), meta = (BlueprintSpawnableComponent))
class INTERACTIVEGUNS_API UCylinderMagazineComponent : public UMagazineComponentBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable)
	UBullet* GetBulletAtIndex(int index);

	UBullet* GetNextBullet() override;

	UFUNCTION(BlueprintCallable)
	bool InsertBulletAtIndex(UBullet* bullet, int index);

	UFUNCTION(BlueprintCallable)
	void IncrementCylinderIndex();

	UFUNCTION(BlueprintCallable)
	void UnloadBulletAtIndex(int index);

	UFUNCTION(BlueprintCallable)
	void HandleBulletClicked(int index);

	UFUNCTION(BlueprintCallable)
	void HandleEjectorClicked();

	UPROPERTY(BlueprintReadOnly)
	int Index;
};
