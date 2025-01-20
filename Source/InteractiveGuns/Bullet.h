// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WeaponData/WeaponDataStructs.h"
#include "Bullet.generated.h"

class UBulletSlotMeshComponent;

/**
 * 
 */
UCLASS(Blueprintable)
class INTERACTIVEGUNS_API UBullet : public UObject
{
	GENERATED_BODY()


protected:
	UPROPERTY(BlueprintReadOnly)
	UBulletSlotMeshComponent* VisualComponent;

public:
	FBulletRecoilData RecoilData;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Fired;

	UPROPERTY(EditAnywhere)
	bool Loaded;

	UFUNCTION(BlueprintCallable)
	bool TryFire();

	void SetVisualComponent(UBulletSlotMeshComponent* component);

	UBulletSlotMeshComponent* GetVisualComponent();
};
