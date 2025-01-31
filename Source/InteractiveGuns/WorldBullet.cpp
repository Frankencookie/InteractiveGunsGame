// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldBullet.h"

// Sets default values
AWorldBullet::AWorldBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	StaticMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWorldBullet::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMeshComponent->SetScalarParameterValueOnMaterials("Fired", bFired ? 1 : 0);
}

// Called every frame
void AWorldBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWorldBullet::Initialise(UStaticMesh* model, bool fired)
{
	bFired = fired;
	StaticMeshComponent->SetStaticMesh(model);
	StaticMeshComponent->SetScalarParameterValueOnMaterials("Fired", fired ? 1 : 0);

	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->AddTorqueInDegrees(StaticMeshComponent->GetForwardVector() * 5.0f);

	if (fired)
		SetLifeSpan(10.0f);
}

bool AWorldBullet::CanInteract_Implementation()
{
	return !bFired;
}
