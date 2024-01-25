// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CoverSystemActorComponent.generated.h"

class ACoverSystemController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COVERSYSTEM_API UCoverSystemActorComponent : public UActorComponent
{
	GENERATED_BODY()



public:	
	// Sets default values for this component's properties
	UCoverSystemActorComponent();

	UPROPERTY(BlueprintReadOnly)
	ACoverSystemController* CoverSystemController;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	ACoverSystemController* GetCoverSystemController();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
