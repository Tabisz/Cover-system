// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CoverSystemController.h"
#include "CoverSystemGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class COVERSYSTEM_API UCoverSystemGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<ACoverSystemController> CoverSystemController;
	
};
