// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponData/WeaponDataStructs.h"
#include "WeaponBase.generated.h"

//Forward declarations
class USceneComponent;

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

	USceneComponent* RootComponent;

	UPROPERTY(EditAnywhere)
	FWeaponOffset WeaponOffsetData;

	UPROPERTY(EditAnywhere)
	FWeaponRecoilData WeaponRecoilData;

	UPROPERTY(EditAnywhere)
	float AimSpeed;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Delegates
	FOnWeaponFiredDelegate OnWeaponFired;

	UFUNCTION(BlueprintCallable)
	void HandleOnWeaponFired();

	UFUNCTION(BlueprintCallable)
	void ShootRaycast(FVector direction, float range);

	UFUNCTION(BlueprintCallable)
	void CalculateRecoil(FRecoilImpulseData& recoilDataOutput);

	UFUNCTION(BlueprintImplementableEvent, Category = "AttackEvents")
	void PrimaryAttack();

	UFUNCTION(BlueprintImplementableEvent, Category = "ManipulateMode")
	void ManipulateModeStart();

	UFUNCTION(BlueprintImplementableEvent, Category = "ManipulateMode")
	void ManipulateModeEnd();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AttackEvents")
	bool CanFire();

	float GetAimSpeed();

	FWeaponOffset GetOffsetData();
};
