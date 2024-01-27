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
	CoverSystemActorComponent->OnRegisterCompleted.AddDynamic(this,&ACoverSystemCharacter::OnCoverSystemInfoRequested);

}

void ACoverSystemCharacter::OnCoverSystemInfoRequested_Implementation()
{
	TMap<FKey, FString> newInfo;
	newInfo.Add(FKey("TEAM"),UEnum::GetValueAsString(myTeam));
	CoverSystemActorComponent->AdditionalInfo = newInfo;
}

AActor* ACoverSystemCharacter::GetBestShootingTarget()
{

	if(!CoverSystemActorComponent || !CoverSystemActorComponent->CurrentCoverPlace) return nullptr;
	if(CoverSystemActorComponent->CurrentCoverPlace->myState != ECoverPlaceState::OCCUPIED) return nullptr;
	auto validTargets = CoverSystemActorComponent->CurrentCoverPlace->GetAllValidTargets();
	if(validTargets.Num()==0) return nullptr;

	AActor* choosenActor = nullptr;
	float shortestTargetDistance = INFINITY;
	for (auto Target : validTargets)
	{
		if(Target->isTooClose) continue;
		CoverSystemActorComponent->OnAdditionalInfoUpdateRequest.Broadcast();

		FString* team = Target->AdditionalInfoMap.Find("TEAM");
		if(team->Equals(*CoverSystemActorComponent->AdditionalInfo.Find("TEAM")))
			continue;
		if(Target->distance<shortestTargetDistance)
			choosenActor = Target->coverSystemComponent->GetOwner();
	}

	return choosenActor;
}

bool ACoverSystemCharacter::ShootAtTarget(AActor* target)
{
	if(target)
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Currently shooting at %s"),*GetDebugName(target)));

	return true;
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

