// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

//Forward declarations
class UCameraComponent;
class USceneComponent;
class AWeaponBase;

UCLASS()
class INTERACTIVEGUNS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeaponBase> starterWeapon;

	AWeaponBase* currentWeapon;

	//Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	USceneComponent* CameraSocket;

	UPROPERTY(EditAnywhere)
	USceneComponent* WeaponSocket;

	//Movement
	UFUNCTION()
	void MoveForward(float value);

	UFUNCTION()
	void MoveRight(float value);

	UFUNCTION()
	void LookUp(float value);

	UFUNCTION()
	void LookRight(float value);

	//Attacking
	UFUNCTION()
	void PrimaryAttack();

	float CameraY = 0;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
