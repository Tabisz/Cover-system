// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CoverActorProperties.generated.h"

/**
 * Clasa przetrzymująca dane dla aktora uzywajacego cover systemu. Steruja one sposobem doboru miejsca przez aktora
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
