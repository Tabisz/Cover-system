// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CoverActorProperties.generated.h"

/**
 * A class that holds data for an actor using the cover system. They control how the actor chooses cover place
 */
UCLASS()
class COVERSYSTEM_API UCoverActorProperties : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	float distanceToCoverSign;

	UPROPERTY(EditDefaultsOnly)
	float canShootOthersSign;

	UPROPERTY(EditDefaultsOnly)
	float canBeShootedSign;
	
};
