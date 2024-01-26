// Fill out your copyright notice in the Description page of Project Settings.


#include "CoverSystemCharacter.h"

#include "CoverSystemController.h"

// Sets default values
ACoverSystemCharacter::ACoverSystemCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CoverSystemActorComponent  = CreateDefaultSubobject<UCoverSystemActorComponent>(TEXT("CoverSystemComponent"));
	CoverSystemActorComponent->OnRegisterCompleted.AddDynamic(this,&ACoverSystemCharacter::OnCoverSystemRegisterCompleted);

}

// Called when the game starts or when spawned
void ACoverSystemCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoverSystemCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACoverSystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

