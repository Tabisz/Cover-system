// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoverPlace.h"
#include "CoverSystemActorComponent.h"
#include "CoverSystemProperties.h"
#include "GameFramework/Actor.h"
#include "CoverSystemController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCoverPlaceStateChangedDelegate,ACoverPlace*, coverPlace, ECoverPlaceState, coverPlaceState);

UCLASS()
class COVERSYSTEM_API ACoverSystemController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoverSystemController();

	FCoverPlaceStateChangedDelegate OnCoverPlaceStateChanged;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<ACoverPlace*> CoverPlaces;
	UPROPERTY(BlueprintReadOnly)
	TArray<UCoverSystemActorComponent*> CoverActors;
	
	UFUNCTION(BlueprintCallable)
	void RegisterNewCover(ACoverPlace* newCover);
	UFUNCTION(BlueprintCallable)
	void UnregisterCover(ACoverPlace* Cover);
	
	UFUNCTION(BlueprintCallable)
	void RegisterNewActor(UCoverSystemActorComponent* newActor);
	UFUNCTION(BlueprintCallable)
	void UnregisterActor(UCoverSystemActorComponent* Actor);

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UCoverSystemProperties* CoverSystemProperties;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
