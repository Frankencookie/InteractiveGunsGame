// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "MuzzleFlashComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (GunComponents), meta = (BlueprintSpawnableComponent))
class INTERACTIVEGUNS_API UMuzzleFlashComponent : public UPointLightComponent
{
	GENERATED_BODY()

public:
	UMuzzleFlashComponent();
	
private:
	UPROPERTY(EditAnywhere)
	UCurveFloat* MuzzleFlashCurve;

	UPROPERTY(EditAnywhere)
	float MaximumBrightness = 3;

	UPROPERTY()
	float CurrentValue;

	float duration = 0.5f;

	bool Active;

	// Called when the game starts
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnRegister() override;

	UFUNCTION()
	void DoMuzzleFlash();

	UFUNCTION()
	void DeactivateFlash();
};
