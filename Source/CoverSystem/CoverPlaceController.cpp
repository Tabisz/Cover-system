// Fill out your copyright notice in the Description page of Project Settings.


#include "CoverPlaceController.h"

// Sets default values
ACoverPlaceController::ACoverPlaceController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACoverPlaceController::RegisterNewCover(ACoverPlace* newCover)
{
	if(newCover)
		CoverPlaces.AddUnique(newCover);
}

void ACoverPlaceController::UnregisterCover(ACoverPlace* Cover)
{
	if(Cover)
		CoverPlaces.Remove(Cover);
}

void ACoverPlaceController::RegisterNewActor(UCoverSystemActorComponent* newActor)
{
	if(newActor)
		CoverActors.AddUnique(newActor);
}

void ACoverPlaceController::UnregisterActor(UCoverSystemActorComponent* Actor)
{
	if(Actor)
		CoverActors.Remove(Actor);
}

// Called when the game starts or when spawned
void ACoverPlaceController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoverPlaceController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

