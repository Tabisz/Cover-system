// Fill out your copyright notice in the Description page of Project Settings.


#include "CoverSystemCharacter.h"

#include "CoverSystemController.h"
#include "DSP/LFO.h"

// Sets default values
ACoverSystemCharacter::ACoverSystemCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Health = 100;
	
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

	if(!CoverSystemActorComponent || !CoverSystemActorComponent->OccupiedCoverPlace) return nullptr;
	if(CoverSystemActorComponent->OccupiedCoverPlace->myState != ECoverPlaceState::OCCUPIED) return nullptr;
	auto validTargets = CoverSystemActorComponent->OccupiedCoverPlace->GetAllValidTargets();
	if(validTargets.Num()==0) return nullptr;

	AActor* choosenActor = nullptr;
	float shortestTargetDistance = INFINITY;
	for (auto Target : validTargets)
	{
		if(Target->isTooClose) continue;
		if(!Target->isInVisibilityRange) continue;
		
		CoverSystemActorComponent->OnAdditionalInfoUpdateRequest.Broadcast();
		
		FString* team = Target->AdditionalInfoMap.Find("TEAM");
		if(team->Equals(*CoverSystemActorComponent->AdditionalInfo.Find("TEAM")))
			continue;
		
		if(Target->distance<shortestTargetDistance)
			choosenActor = Target->coverSystemComponent->GetOwner();
	}

	return choosenActor;
}

void ACoverSystemCharacter::ShootAtTarget(AActor* target)
{
	if(target)
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Currently shooting at %s"),*GetDebugName(target)));
	if(auto enemy = Cast<ACoverSystemCharacter>(target))
		enemy->ReceiveDamage(30);
	
}

void ACoverSystemCharacter::ReceiveDamage(float amount)
{
	Health -= amount;
	if(Health<=0)
		Die();
}

void ACoverSystemCharacter::Die()
{
	CoverSystemActorComponent->CoverSystemController->UnregisterActor(CoverSystemActorComponent);
	CoverSystemActorComponent->FreeUpCoverPlace();
	if(CoverSystemActorComponent->RegisteredCoverPlace)
		CoverSystemActorComponent->RegisteredCoverPlace->ChangeState(ECoverPlaceState::FREE);
				
	
	Destroy();
}

