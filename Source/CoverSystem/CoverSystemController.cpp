// Fill out your copyright notice in the Description page of Project Settings.


#include "CoverSystemController.h"

// Sets default values
ACoverSystemController::ACoverSystemController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACoverSystemController::RegisterNewCover(ACoverPlace* newCover)
{
	if(newCover)
		CoverPlaces.AddUnique(newCover);
}

void ACoverSystemController::UnregisterCover(ACoverPlace* Cover)
{
	if(Cover)
		CoverPlaces.Remove(Cover);
}

void ACoverSystemController::RegisterNewActor(UCoverSystemActorComponent* newActor)
{
	if(newActor)
		CoverActors.AddUnique(newActor);
}

void ACoverSystemController::UnregisterActor(UCoverSystemActorComponent* Actor)
{
	if(Actor)
		CoverActors.Remove(Actor);
}

// Called when the game starts or when spawned
void ACoverSystemController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoverSystemController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

