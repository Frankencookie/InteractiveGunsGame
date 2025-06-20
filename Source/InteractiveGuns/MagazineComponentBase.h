// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Bullet.h"
#include "MagazineComponentBase.generated.h"

class UBulletSlotMeshComponent;

UCLASS()
class INTERACTIVEGUNS_API UMagazineComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMagazineComponentBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UBullet*> bullets;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UBulletSlotMeshComponent*> bulletMeshComponents;

	UPROPERTY(EditAnywhere)
	int MagazineSize = 6;

	UPROPERTY(BlueprintReadOnly)
	int BulletCount;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual UBullet* GetNextBullet();

	UPROPERTY(BlueprintReadWrite)
	bool MagazineRemoved;
};
