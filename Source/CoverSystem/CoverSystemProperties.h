// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CoverSystemProperties.generated.h"

/**
 * 
 */
UCLASS()
class COVERSYSTEM_API UCoverSystemProperties : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	float MaxVisibilityDistance;

	UPROPERTY(EditDefaultsOnly)
	float MinVisibilityDistance;

	UPROPERTY(EditDefaultsOnly)
	float VisibilityAngleRange;
	
};
