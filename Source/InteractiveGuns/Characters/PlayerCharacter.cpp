// Fill out your copyright notice in the Description page of Project Settings.


#include "../Characters/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "../WeaponData/WeaponDataStructs.h"
#include "../WeaponBase.h"
#include "../Interactable.h"
#include "../GameCharacterMovementComponent.h"
#include "../InventoryComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Components
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraSocket = CreateDefaultSubobject<USceneComponent>(TEXT("CameraSocket"));
	WeaponBaseSocket = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponBaseSocket"));

	WeaponMomentumSocket = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponMomentumSocket"));
	FreeAimSocket = CreateDefaultSubobject<USceneComponent>(TEXT("FreeAimSocket"));

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));


	//Attachment
	CameraSocket->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(CameraSocket);

	WeaponBaseSocket->SetupAttachment(CameraSocket);

	FreeAimSocket->SetupAttachment(WeaponBaseSocket);
	WeaponMomentumSocket->SetupAttachment(FreeAimSocket);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent = Cast<UGameCharacterMovementComponent>(GetMovementComponent());

	if (CurrentWeapon == nullptr && StarterWeapon != nullptr)
	{
		EquipWeapon(GetWorld()->SpawnActor<AWeaponBase>(StarterWeapon));
	}
}

void APlayerCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void APlayerCharacter::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

void APlayerCharacter::LookUp(float value)
{
	if (bManipulateMode)
		return;
	CameraY += value;
	CameraY = FMath::Clamp(CameraY, -85.0f, 85.0f);
	CameraSocket->SetRelativeRotation(FRotator(CameraY, 0, 0));

	if (CurrentWeapon == nullptr)
		return;

	WeaponMomentumTarget.Pitch = FMath::Clamp(value * 5.0f, -30.0f, 30.0f);

	float multiplier = bAiming ? 0.5f : 1.0f;

	FreeAimTargetPosition += FVector(0.0f, 0.0f, value * multiplier);
	FreeAimTargetRotation += FRotator(value * multiplier, 0.0f, 0.0f);

	FreeAimTargetPosition.Z = FMath::Clamp(FreeAimTargetPosition.Z, -3.0f, 3.0f);
	FreeAimTargetRotation.Pitch = FMath::Clamp(FreeAimTargetRotation.Pitch, -2.0f, 2.0f);
}

void APlayerCharacter::LookRight(float value)
{
	if (bManipulateMode)
		return;

	AddControllerYawInput(value);

	if (CurrentWeapon == nullptr)
		return;

	WeaponMomentumTarget.Yaw = FMath::Clamp(value * 5.0f, -30.0f, 30.0f);

	float multiplier = bAiming ? 0.5f : 1.0f;

	FreeAimTargetPosition += FVector(0.0f, value * multiplier, 0.0f);
	FreeAimTargetRotation += FRotator(0.0f, value * multiplier, 0.0f);

	FreeAimTargetPosition.Y = FMath::Clamp(FreeAimTargetPosition.Y, -2.0f * multiplier, 2.0f * multiplier);
	FreeAimTargetRotation.Yaw = FMath::Clamp(FreeAimTargetRotation.Yaw, -5.0f, 5.0f);
}

void APlayerCharacter::StartAiming()
{
	MovementComponent->BeginAiming();
	bAiming = true;
}

void APlayerCharacter::EndAiming()
{
	MovementComponent->EndAiming();
	bAiming = false;
}

void APlayerCharacter::ManipulateModeStart()
{
	bManipulateMode = true;
	
	APlayerController* controller = Cast<APlayerController>(GetController());

	controller->bShowMouseCursor = true;
	controller->bEnableMouseOverEvents = true;
	controller->bEnableClickEvents = true;

	if (CurrentWeapon == nullptr)
		return;

	CurrentWeapon->ManipulateModeStart();

	OnManipulateModeStart();
}

void APlayerCharacter::ManipulateModeEnd()
{
	bManipulateMode = false;

	APlayerController* controller = Cast<APlayerController>(GetController());

	controller->bShowMouseCursor = false;
	controller->bEnableMouseOverEvents = false;
	controller->bEnableClickEvents = false;

	if (CurrentWeapon == nullptr)
		return;

	CurrentWeapon->ManipulateModeEnd();

	OnManipulateModeEnd();
}

void APlayerCharacter::PrimaryAttack()
{
	if (CurrentWeapon != nullptr && !bManipulateMode)
	{
		CurrentWeapon->PrimaryAttack();
	}
}

void APlayerCharacter::CockHammer(float value)
{
	if (value < 0.1f)
		return;

	if (CurrentWeapon != nullptr)
	{
		CurrentWeapon->CockHammer();
	}
}

void APlayerCharacter::Interact()
{
	if (bManipulateMode || bAiming)
		return;

	//Set up Variables
	FHitResult hitResult;
	FCollisionQueryParams CollisionParameters;

	CollisionParameters.AddIgnoredActor(this);

	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = ((CameraComponent->GetForwardVector() * InteractRange) + Start);

	//DebugLine
	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5, 0, 1);

	//Perform Raycast and apply damage
	if (GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECC_WorldDynamic, CollisionParameters))
	{
		//GLog->Log(hitResult.GetActor()->GetFullName());
		if (hitResult.GetActor() != nullptr)
		{
			AActor* actorPtr = hitResult.GetActor();

			IInteractable* InteractableInterface = Cast<IInteractable>(actorPtr);

			if(InteractableInterface)
				IInteractable::Execute_OnInteract(actorPtr, this);
		}
	}
}

void APlayerCharacter::ApplyRecoil()
{
	if (CurrentWeapon != nullptr)
	{
		FRecoilImpulseData recoilData;
		CurrentWeapon->CalculateRecoil(recoilData);
		RecoilPositionTarget += recoilData.PositionRecoilImpulse;
		RecoilRotationTarget += recoilData.RotationRecoilImpulse;

		RecoilShock += 15.0f;

		FreeAimTargetPosition += FVector(0.0f, 0.0f, 2.0f);
		FreeAimTargetPosition.Z = FMath::Clamp(FreeAimTargetPosition.Z, -3.0f, 3.0f);
	}
}

void APlayerCharacter::EquipWeapon(AWeaponBase* newWeapon)
{
	//Handle old weapon
	if (CurrentWeapon != nullptr)
	{
		CurrentWeapon->OnWeaponFired.Unbind();
	}

	CurrentWeapon = newWeapon;
	if (CurrentWeapon != nullptr)
	{
		WeaponBaseSocket->SetRelativeLocation(CurrentWeapon->GetOffsetData().OffsetFromWielder);
		CurrentWeapon->OnWeaponFired.BindUObject(this, &APlayerCharacter::ApplyRecoil);
	}
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentWeapon == nullptr)
		return;

	FVector targetPosition;
	FRotator targetRotation;

	FWeaponOffset offsetData = CurrentWeapon->GetOffsetData();

	if (bManipulateMode)
	{
		targetPosition = offsetData.ManipulateModeOffsetFromWielder;
		targetRotation = offsetData.ManipulateModeRotation;

		FreeAimTargetPosition = FMath::Lerp(FreeAimTargetPosition, FVector::ZeroVector, DeltaTime * 5.0f);
		FreeAimTargetRotation = FMath::Lerp(FreeAimTargetRotation, FRotator::ZeroRotator, DeltaTime * 5.0f);
	}
	else
	{
		if (bAiming)
		{
			targetPosition = offsetData.AimingOffsetFromWielder;

			FreeAimTargetPosition = FMath::Lerp(FreeAimTargetPosition, FVector::ZeroVector, DeltaTime * 5.0f);
			FreeAimTargetRotation = FMath::Lerp(FreeAimTargetRotation, FRotator::ZeroRotator, DeltaTime * 5.0f);
		}
		else
		{
			targetPosition = offsetData.OffsetFromWielder;
		}
		
		targetRotation = AimingRotation;
	}

	RecoilPositionTarget = FMath::Lerp(RecoilPositionTarget, 0.0f, DeltaTime * 8.0f);
	RecoilRotationTarget = FMath::Lerp(RecoilRotationTarget, FRotator::ZeroRotator, DeltaTime * 8.0f);

	targetPosition += RecoilPositionTarget;
	targetRotation += RecoilRotationTarget;

	WeaponBaseSocket->SetRelativeLocation(FMath::Lerp(WeaponBaseSocket->GetRelativeLocation(), targetPosition, DeltaTime * CurrentWeapon->GetAimSpeed()));
	WeaponBaseSocket->SetRelativeRotation(FMath::Lerp(WeaponBaseSocket->GetRelativeRotation(), targetRotation, DeltaTime * (10 + RecoilShock)));

	RecoilShock -= DeltaTime * 50.0f;
	if (RecoilShock < 0)
		RecoilShock = 0;

	WeaponMomentumSocket->SetRelativeRotation(FMath::Lerp(WeaponMomentumSocket->GetRelativeRotation(), WeaponMomentumTarget, DeltaTime * 5.0f));
	FreeAimSocket->SetRelativeLocation(FMath::Lerp(FreeAimSocket->GetRelativeLocation(), FreeAimTargetPosition, DeltaTime * 10.0f));
	FreeAimSocket->SetRelativeRotation(FMath::Lerp(FreeAimSocket->GetRelativeRotation(), FreeAimTargetRotation, DeltaTime * 10.0f));

	CurrentWeapon->SetActorLocation(WeaponMomentumSocket->GetComponentLocation());
	CurrentWeapon->SetActorRotation(WeaponMomentumSocket->GetComponentRotation());
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::LookRight);

	PlayerInputComponent->BindAxis("CockHammer", this, &APlayerCharacter::CockHammer);

	PlayerInputComponent->BindAction("PrimaryAttack", EInputEvent::IE_Pressed, this, &APlayerCharacter::PrimaryAttack);

	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &APlayerCharacter::StartAiming);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &APlayerCharacter::EndAiming);

	PlayerInputComponent->BindAction("ManipulateMode", EInputEvent::IE_Pressed, this, &APlayerCharacter::ManipulateModeStart);
	PlayerInputComponent->BindAction("ManipulateMode", EInputEvent::IE_Released, this, &APlayerCharacter::ManipulateModeEnd);

	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &APlayerCharacter::Interact);
}

UInventoryComponent* APlayerCharacter::GetInventory()
{
	return InventoryComponent;
}
