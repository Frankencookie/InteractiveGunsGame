// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "StrikerComponent.generated.h"

class USoundBase;
/**
 * 
 */
UCLASS(ClassGroup = (GunComponents), meta = (BlueprintSpawnableComponent))
class INTERACTIVEGUNS_API UStrikerComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UStrikerComponent();
	
protected:

	UPROPERTY(EditAnywhere)
	FVector CockedPosition;

	UPROPERTY(EditAnywhere)
	FRotator CockedRotation;

	FRotator UncockedRotation;
	FVector UncockedPosition;

	UPROPERTY(EditAnywhere)
	USoundBase* CockedSound;

	UPROPERTY(EditAnywhere)
	USoundBase* StrikeSound;

	UPROPERTY(EditAnywhere)
	float CockTime = 0.2f;

	float LerpValue;

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	bool Cocked;

	bool Cocking;

	bool UnCocked;

public:

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnRegister() override;

	UFUNCTION(BlueprintCallable)
	void CockStriker();

	UFUNCTION(BlueprintCallable)
	void UncockStriker();

	UFUNCTION(BlueprintCallable)
	bool StrikeStriker();
};
