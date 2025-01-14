// Fill out your copyright notice in the Description page of Project Settings.


#include "../Characters/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
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
		WeaponSocket->SetRelativeLocation(currentWeapon->GetOffset(false));
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
	CameraY += value;
	CameraY = FMath::Clamp(CameraY, -85.0f, 85.0f);
	CameraSocket->SetRelativeRotation(FRotator(CameraY, 0, 0));
}

void APlayerCharacter::LookRight(float value)
{
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
}

void APlayerCharacter::ManipulateModeEnd()
{
	manipulateMode = false;
}

void APlayerCharacter::PrimaryAttack()
{
	if (currentWeapon != nullptr && !manipulateMode)
	{
		currentWeapon->PrimaryAttack();
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

	if (manipulateMode)
	{
		targetPosition = currentWeapon->GetManipulateModeOffset();
		targetRotation = currentWeapon->GetManipulateModeRotation();
	}
	else
	{
		targetPosition = currentWeapon->GetOffset(aiming);
		targetRotation = AimingRotation;
	}

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