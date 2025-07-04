// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponData/WeaponDataStructs.h"
#include "WeaponBase.generated.h"

//Forward declarations
class USceneComponent;
class USoundBase;
class UMuzzleFlashComponent;

DECLARE_DELEGATE(FOnWeaponFiredDelegate)


UCLASS(Blueprintable)
class INTERACTIVEGUNS_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* MuzzlePos;

	USceneComponent* GunRootComponent;

	UPROPERTY(EditAnywhere)
	USoundBase* GunshotSound;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UMuzzleFlashComponent* MuzzleFlashComponent;

	UPROPERTY(EditAnywhere)
	FWeaponOffset WeaponOffsetData;

	UPROPERTY(EditAnywhere)
	FWeaponRecoilData WeaponRecoilData;

	UPROPERTY(EditAnywhere)
	float AimSpeed;

	UPROPERTY(BlueprintReadWrite)
	bool TryingToFire;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Delegates
	FOnWeaponFiredDelegate OnWeaponFired;

	UFUNCTION(BlueprintCallable)
	void HandleOnWeaponFired();

	UFUNCTION(BlueprintCallable)
	void CalculateRecoil(FRecoilImpulseData& recoilDataOutput);

	UFUNCTION(BlueprintImplementableEvent, Category = "AttackEvents")
	void PrimaryAttack();

	UFUNCTION(BlueprintImplementableEvent, Category = "AttackEvents")
	void CockHammer();

	UFUNCTION(BlueprintImplementableEvent, Category = "ManipulateMode")
	void ManipulateModeStart();

	UFUNCTION(BlueprintImplementableEvent, Category = "ManipulateMode")
	void ManipulateModeEnd();

	UFUNCTION(BlueprintCallable)
	void ShootRaycast(FVector direction, float range);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AttackEvents")
	bool CanFire();

	float GetAimSpeed();

	FWeaponOffset GetOffsetData();
};
