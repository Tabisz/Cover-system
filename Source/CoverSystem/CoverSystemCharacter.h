// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoverSystemActorComponent.h"
#include "GameFramework/Character.h"
#include "CoverSystemCharacter.generated.h"


UENUM(BlueprintType)
enum class ETEAM : uint8
{
	RED,  
	BLUE,
};
UCLASS()
class COVERSYSTEM_API ACoverSystemCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	UCoverSystemActorComponent* CoverSystemActorComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	ETEAM myTeam;
	

	ACoverSystemCharacter();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCoverSystemRegisterCompleted();

protected:
	virtual void BeginPlay() override;
	

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
