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

	if (currentWeapon == nullptr && starterWeapon != nullptr)
	{
		currentWeapon = GetWorld()->SpawnActor<AWeaponBase>(starterWeapon);
		WeaponSocket->SetRelativeLocation(currentWeapon->GetOffsetData().OffsetFromWielder);
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

	if (currentWeapon == nullptr)
		return;

	currentWeapon->ManipulateModeStart();
}

void APlayerCharacter::ManipulateModeEnd()
{
	manipulateMode = false;

	APlayerController* controller = Cast<APlayerController>(GetController());

	controller->bShowMouseCursor = false;
	controller->bEnableMouseOverEvents = false;
	controller->bEnableClickEvents = false;

	if (currentWeapon == nullptr)
		return;

	currentWeapon->ManipulateModeEnd();
}

void APlayerCharacter::PrimaryAttack()
{
	if (currentWeapon != nullptr && !manipulateMode)
	{
		FRecoilImpulseData recoilData;

		currentWeapon->CalculateRecoil(recoilData);

		if (currentWeapon->CanFire())
		{
			currentWeapon->PrimaryAttack();
			RecoilPositionTarget += recoilData.PositionRecoilImpulse;
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (currentWeapon == nullptr)
		return;

	FVector targetPosition;
	FRotator targetRotation;

	FWeaponOffset offsetData = currentWeapon->GetOffsetData();

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

	RecoilPositionTarget = FMath::Lerp(RecoilPositionTarget, 0.0f, DeltaTime * 10.0f);

	targetPosition += RecoilPositionTarget;

	WeaponSocket->SetRelativeLocation(FMath::Lerp(WeaponSocket->GetRelativeLocation(), targetPosition, DeltaTime * currentWeapon->GetAimSpeed()));
	WeaponSocket->SetRelativeRotation(FMath::Lerp(WeaponSocket->GetRelativeRotation(), targetRotation, DeltaTime * 10));

	currentWeapon->SetActorLocation(WeaponSocket->GetComponentLocation());
	currentWeapon->SetActorRotation(WeaponSocket->GetComponentRotation());
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