// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoverSystemActorComponent.h"
#include "GameFramework/Character.h"
#include "CoverSystemCharacter.generated.h"

UCLASS()
class COVERSYSTEM_API ACoverSystemCharacter : public ACharacter
{
	GENERATED_BODY()

	UCoverSystemActorComponent* CoverSystemActorComponent;

public:
	// Sets default values for this character's properties
	ACoverSystemCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
