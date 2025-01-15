// Fill out your copyright notice in the Description page of Project Settings.


#include "../Characters/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "../WeaponData/WeaponDataStructs.h"
#include "../WeaponBase.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Components
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraSocket = CreateDefaultSubobject<USceneComponent>(TEXT("CameraSocket"));
	WeaponSocket = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponSocket"));


	//Attachment
	CameraSocket->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(CameraSocket);
	WeaponSocket->SetupAttachment(CameraSocket);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

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
	if (manipulateMode)
		return;
	CameraY += value;
	CameraY = FMath::Clamp(CameraY, -85.0f, 85.0f);
	CameraSocket->SetRelativeRotation(FRotator(CameraY, 0, 0));
}

void APlayerCharacter::LookRight(float value)
{
	if (manipulateMode)
		return;

	AddControllerYawInput(value);
}

void APlayerCharacter::StartAiming()
{
	aiming = true;
}

void APlayerCharacter::EndAiming()
{
	aiming = false;
}

void APlayerCharacter::ManipulateModeStart()
{
	manipulateMode = true;
	
	APlayerController* controller = Cast<APlayerController>(GetController());

	controller->bShowMouseCursor = true;
	controller->bEnableMouseOverEvents = true;
	controller->bEnableClickEvents = true;

	if (CurrentWeapon == nullptr)
		return;

	CurrentWeapon->ManipulateModeStart();
}

void APlayerCharacter::ManipulateModeEnd()
{
	manipulateMode = false;

	APlayerController* controller = Cast<APlayerController>(GetController());

	controller->bShowMouseCursor = false;
	controller->bEnableMouseOverEvents = false;
	controller->bEnableClickEvents = false;

	if (CurrentWeapon == nullptr)
		return;

	CurrentWeapon->ManipulateModeEnd();
}

void APlayerCharacter::PrimaryAttack()
{
	if (CurrentWeapon != nullptr && !manipulateMode)
	{
		if (CurrentWeapon->CanFire())
		{
			CurrentWeapon->PrimaryAttack();
		}
	}
}

void APlayerCharacter::ApplyRecoil()
{
	if (CurrentWeapon != nullptr && !manipulateMode)
	{
		FRecoilImpulseData recoilData;
		CurrentWeapon->CalculateRecoil(recoilData);
		RecoilPositionTarget += recoilData.PositionRecoilImpulse;
		RecoilRotationTarget += recoilData.RotationRecoilImpulse;

		RecoilShock += 15.0f;
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
		WeaponSocket->SetRelativeLocation(CurrentWeapon->GetOffsetData().OffsetFromWielder);
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

	if (manipulateMode)
	{
		targetPosition = offsetData.ManipulateModeOffsetFromWielder;
		targetRotation = offsetData.ManipulateModeRotation;
	}
	else
	{
		if (aiming)
		{
			targetPosition = offsetData.AimingOffsetFromWielder;
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

	WeaponSocket->SetRelativeLocation(FMath::Lerp(WeaponSocket->GetRelativeLocation(), targetPosition, DeltaTime * CurrentWeapon->GetAimSpeed()));
	WeaponSocket->SetRelativeRotation(FMath::Lerp(WeaponSocket->GetRelativeRotation(), targetRotation, DeltaTime * (10 + RecoilShock)));

	RecoilShock -= DeltaTime * 50.0f;
	if (RecoilShock < 0)
		RecoilShock = 0;

	CurrentWeapon->SetActorLocation(WeaponSocket->GetComponentLocation());
	CurrentWeapon->SetActorRotation(WeaponSocket->GetComponentRotation());
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::LookRight);

	PlayerInputComponent->BindAction("PrimaryAttack", EInputEvent::IE_Pressed, this, &APlayerCharacter::PrimaryAttack);

	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &APlayerCharacter::StartAiming);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &APlayerCharacter::EndAiming);

	PlayerInputComponent->BindAction("ManipulateMode", EInputEvent::IE_Pressed, this, &APlayerCharacter::ManipulateModeStart);
	PlayerInputComponent->BindAction("ManipulateMode", EInputEvent::IE_Released, this, &APlayerCharacter::ManipulateModeEnd);
}