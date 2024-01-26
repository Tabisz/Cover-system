// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawningController.h"

#include "CoverSystemCharacter.h"

// Sets default values
ASpawningController::ASpawningController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASpawningController::SpawnActorAtRandomPlace(TSubclassOf<ACoverSystemCharacter> AnotherClass, TArray<AActor*> spawningPlacesPool)
{
	auto spawnPlace = spawningPlacesPool[FMath::RandRange(0, spawningPlacesPool.Num()-1)];
	if(!spawnPlace) return;
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<AActor>(AnotherClass,spawnPlace->GetActorLocation(), FRotator::ZeroRotator, SpawnInfo);
}

// Called when the game starts or when spawned
void ASpawningController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawningController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

