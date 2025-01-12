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


	//Attachment
	CameraSocket->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(CameraSocket);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (currentWeapon == nullptr && starterWeapon != nullptr)
	{
		currentWeapon = GetWorld()->SpawnActor<AWeaponBase>(starterWeapon);
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

void APlayerCharacter::PrimaryAttack()
{
	if (currentWeapon != nullptr)
	{
		currentWeapon->PrimaryAttack();
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (currentWeapon != nullptr)
	{
		currentWeapon->SetActorLocation(CameraSocket->GetComponentLocation());
		currentWeapon->SetActorRotation(CameraSocket->GetComponentRotation());
	}
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
}