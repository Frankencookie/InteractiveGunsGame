// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacterMovementComponent.h"

void UGameCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	DefaultMovementSpeed = MaxWalkSpeed;
	DefaultCrouchedMovementSpeed = MaxWalkSpeedCrouched;
}

void UGameCharacterMovementComponent::BeginAiming()
{
	MaxWalkSpeed = AimingMovementSpeed;
	MaxWalkSpeedCrouched = AimingMovementSpeedCrouched;
}

void UGameCharacterMovementComponent::EndAiming()
{
	MaxWalkSpeed = DefaultMovementSpeed;
	MaxWalkSpeedCrouched = DefaultCrouchedMovementSpeed;
}
