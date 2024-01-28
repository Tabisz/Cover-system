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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;
	

	ACoverSystemCharacter();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCoverSystemRegisterCompleted();
	
	UFUNCTION(BlueprintNativeEvent)
	void OnCoverSystemInfoRequested();

	UFUNCTION(BlueprintCallable)
	AActor* GetBestShootingTarget(); 

	UFUNCTION(BlueprintCallable)
	void ShootAtTarget(AActor* target);

	UFUNCTION(BlueprintCallable)
	void ReceiveDamage(float amount);

	UFUNCTION(BlueprintCallable)
	void Die();

};
