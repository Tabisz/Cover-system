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

ACoverPlace* ACoverSystemController::GetBestCoverPlace(UCoverSystemActorComponent* ActorRequesting)
{
	if(CoverPlaces.Num()== 0)
		return nullptr;
	
	auto coverPlaceWithBestScore = CoverPlaces[0];
	int bestScore = -999999999;

	ActorRequesting->OnAdditionalInfoUpdateRequest.Broadcast();
	
	for (auto place : CoverPlaces)
	{
		if(place == nullptr) continue;
		if(place->myState != ECoverPlaceState::FREE) continue;
		float distanceToCover = FVector::Distance(ActorRequesting->GetOwner()->GetActorLocation(),
											  place->GetActorLocation());
		if(distanceToCover<100) continue;// if cover is too close ignore it
		
		int currentCoverScore = 0;
		
		auto TargetInfos = place->GetAllValidTargets();
		for (auto TargetInfo : TargetInfos)
		{
			if(TargetInfo->coverSystemComponent == ActorRequesting) continue;//ignore self
			
			FString* team = TargetInfo->AdditionalInfoMap.Find("TEAM");
			if(team == ActorRequesting->AdditionalInfo.Find("TEAM")) continue;
				
			
			if(TargetInfo->isTooClose)
				continue;			//this target doesnt affect this place in any way
			
			if(TargetInfo->isInVisibilityRange)
			{
				currentCoverScore+=100/TargetInfo->distance;		//good position because you can shoot others
																	//closer -> better
			}
			
			if(TargetInfo->isAbleToSeeYou)
			{
				if(TargetInfo->isFromCoveredSide)
					currentCoverScore-=5;	//it is bad that someone can see you but you are in cover
				else
					currentCoverScore-=10; //or not
			}
		}

		currentCoverScore-= distanceToCover/100; //more distance is worse
		
		if(currentCoverScore>bestScore)
		{
			bestScore = currentCoverScore;
			coverPlaceWithBestScore = place;
		}
	}
	
	return coverPlaceWithBestScore;
}

ACoverPlace* ACoverSystemController::GetRandomCoverPlace(UCoverSystemActorComponent* ActorRequesting)
{
	if(CoverPlaces.Num()== 0)
		return nullptr;
	
	return CoverPlaces[FMath::RandRange(1, CoverPlaces.Num()-1) ];
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

