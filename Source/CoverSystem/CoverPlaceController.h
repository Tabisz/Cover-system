// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoverPlace.h"
#include "CoverSystemActorComponent.h"
#include "GameFramework/Actor.h"
#include "CoverPlaceController.generated.h"

UCLASS()
class COVERSYSTEM_API ACoverPlaceController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoverPlaceController();
private:
	TArray<ACoverPlace*> CoverPlaces;
	TArray<UCoverSystemActorComponent*> CoverActors;

public:
	UFUNCTION(BlueprintCallable)
	void RegisterNewCover(ACoverPlace* newCover);
	UFUNCTION(BlueprintCallable)
	void UnregisterCover(ACoverPlace* Cover);
	
	UFUNCTION(BlueprintCallable)
	void RegisterNewActor(UCoverSystemActorComponent* newActor);
	UFUNCTION(BlueprintCallable)
	void UnregisterActor(UCoverSystemActorComponent* Actor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
