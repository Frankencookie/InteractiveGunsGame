// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Pickup.generated.h"

UCLASS(Blueprintable)
class INTERACTIVEGUNS_API APickup : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnInteract_Implementation(APlayerCharacter* user) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanInteract();

	virtual bool CanInteract_Implementation();
};
