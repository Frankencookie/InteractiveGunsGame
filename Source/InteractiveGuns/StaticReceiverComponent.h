// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReceiverComponent.h"
#include "StaticReceiverComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (GunComponents), meta = (BlueprintSpawnableComponent))
class INTERACTIVEGUNS_API UStaticReceiverComponent : public UReceiverComponent
{
	GENERATED_BODY()
	
public:
	bool HammerStruck(UMagazineComponentBase* currentMagazine) override;
};
