// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.h"
#include "WorldBullet.generated.h"

UCLASS()
class INTERACTIVEGUNS_API AWorldBullet : public APickup
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	bool bFired;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialise(UStaticMesh* model, bool fired);

	virtual bool CanInteract_Implementation() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
};
