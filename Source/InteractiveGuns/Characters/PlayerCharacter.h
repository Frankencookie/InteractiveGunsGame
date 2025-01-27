// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

//Forward declarations
class UCameraComponent;
class USceneComponent;
class AWeaponBase;
class UGameCharacterMovementComponent;
class UInventoryComponent;

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
	TSubclassOf<AWeaponBase> StarterWeapon;

	AWeaponBase* CurrentWeapon;

	//Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	USceneComponent* CameraSocket;

	UPROPERTY(EditAnywhere)
	USceneComponent* WeaponSocket;

	UGameCharacterMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadOnly)
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere)
	float InteractRange = 100.0f;

#pragma region Input

	//Movement
	UFUNCTION()
	void MoveForward(float value);

	UFUNCTION()
	void MoveRight(float value);

	UFUNCTION()
	void LookUp(float value);

	UFUNCTION()
	void LookRight(float value);

	UFUNCTION()
	void StartAiming();

	UFUNCTION()
	void EndAiming();

	UFUNCTION()
	void ManipulateModeStart();

	UFUNCTION()
	void ManipulateModeEnd();

	//Attacking
	UFUNCTION()
	void PrimaryAttack();

	UFUNCTION()
	void CockHammer(float value);

	UFUNCTION()
	void Interact();

#pragma endregion

	float CameraY = 0;

	float RecoilShock;

	UPROPERTY(BlueprintReadOnly)
	bool bAiming;

	UPROPERTY(BlueprintReadOnly)
	bool bManipulateMode;

	//Aiming and recoil
	FRotator AimingRotation;

	FVector RecoilPositionTarget;
	FRotator RecoilRotationTarget;

	UFUNCTION()
	void ApplyRecoil();

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(AWeaponBase* newWeapon);

	UFUNCTION(BlueprintImplementableEvent)
	void OnManipulateModeStart();

	UFUNCTION(BlueprintImplementableEvent)
	void OnManipulateModeEnd();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UInventoryComponent* GetInventory();
};
