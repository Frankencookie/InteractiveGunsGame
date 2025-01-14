// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponData/WeaponDataStructs.h"
#include "WeaponBase.generated.h"

//Forward declarations
class USceneComponent;


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
	float AimSpeed;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ShootRaycast(FVector direction, float range);

	UFUNCTION(BlueprintImplementableEvent)
	void PrimaryAttack();

	float GetAimSpeed();

	FWeaponOffset GetOffsetData();
};
