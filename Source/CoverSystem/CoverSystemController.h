// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoverPlace.h"
#include "CoverSystemActorComponent.h"
#include "GameFramework/Actor.h"
#include "CoverSystemController.generated.h"

UCLASS()
class COVERSYSTEM_API ACoverSystemController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoverSystemController();
	
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

	
	UFUNCTION(BlueprintCallable)
	ACoverPlace* GetRandomCoverPlace(UCoverSystemActorComponent* ActorRequesting);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
