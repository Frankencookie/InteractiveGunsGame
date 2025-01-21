// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class INTERACTIVEGUNS_API UGameCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	
protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	bool aiming;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
	float AimingMovementSpeed = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
	float AimingMovementSpeedCrouched = 25.0f;

	float DefaultMovementSpeed;
	float DefaultCrouchedMovementSpeed;

public:

	UFUNCTION(BlueprintCallable)
	void BeginAiming();

	UFUNCTION(BlueprintCallable)
	void EndAiming();

};
