// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoverSystemCharacter.h"
#include "GameFramework/Actor.h"
#include "SpawningController.generated.h"

UCLASS()
class COVERSYSTEM_API ASpawningController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawningController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<AActor*> RedSpawnPlaces;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<AActor*> BlueSpawnPlaces;
	
	UFUNCTION(BlueprintCallable)
	void SpawnActorAtRandomPlace(TSubclassOf<ACoverSystemCharacter> AnotherClass, TArray<AActor*> spawningPlacesPool);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
