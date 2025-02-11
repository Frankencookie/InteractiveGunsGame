// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "BulletSlotMeshComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBulletClickedDelegate, int, index);

class AWorldBullet;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INTERACTIVEGUNS_API UBulletSlotMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	int Index;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWorldBullet> WorldBulletType;

	bool bAnimating;
	bool bInserting;

	float AnimationProgress;

	UPROPERTY(EditAnywhere)
	FVector RemovedRelativePosition;

	UPROPERTY(EditAnywhere)
	float AnimationSpeed = 1.0f;

	FVector InsertedPosition;

	void SetAnimationData(FVector StartPos, FVector EndPos, bool IsInserting);

	FVector AnimationStartPos;
	FVector AnimationEndPos;

	bool bFired;

public:

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnRegister() override;

	UPROPERTY(BlueprintAssignable)
	FOnBulletClickedDelegate OnBulletClicked;

	UFUNCTION()
	void OnBulletClickHandler();

	UFUNCTION()
	void InsertBullet();

	UFUNCTION()
	void RemoveBullet();

	UFUNCTION()
	void SetIndex(int value);

	UFUNCTION(BlueprintCallable)
	void SetFired(bool value = true);
};
