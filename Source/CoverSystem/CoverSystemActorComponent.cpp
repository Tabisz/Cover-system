

#include "CoverSystemActorComponent.h"

#include "CoverSystemGameInstance.h"
#include "DSP/LFO.h"
#include "Kismet/GameplayStatics.h"

UCoverSystemActorComponent::UCoverSystemActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	auto myActor = GetOwner();
	if(myActor)
		myActor->Tags.Add(FName("Character"));// move to some sort of global variable
	
}


// Called when the game starts
void UCoverSystemActorComponent::BeginPlay()
{
	Super::BeginPlay();
	CoverSystemController = GetCoverSystemController();
	if(!CoverSystemController)
		return;
	CoverSystemController->RegisterNewActor(this);
	OnRegisterCompleted.Broadcast();
	
}

void UCoverSystemActorComponent::FreeUpCoverPlace()
{
	if(OccupiedCoverPlace)
	{
		OccupiedCoverPlace->ChangeState(ECoverPlaceState::FREE);
		OccupiedCoverPlace = nullptr;
	}
}

bool UCoverSystemActorComponent::RegisterCoverPlace(ACoverPlace* coverPlace)
{
	if(coverPlace->myState != ECoverPlaceState::FREE) return false;
	coverPlace->ChangeState(ECoverPlaceState::REGISTERED);
	RegisteredCoverPlace = coverPlace;
	return true;
}

bool UCoverSystemActorComponent::OccupyRegisteredCoverPlace()
{
	if(RegisteredCoverPlace == nullptr || RegisteredCoverPlace->myState != ECoverPlaceState::REGISTERED) return false;
	OccupiedCoverPlace = RegisteredCoverPlace;
	RegisteredCoverPlace = nullptr;
	OccupiedCoverPlace->ChangeState(ECoverPlaceState::OCCUPIED);
	return true;
}

ACoverPlace* UCoverSystemActorComponent::GetBestCoverPlace()
{
	if(CoverSystemController->CoverPlaces.Num()== 0)
		return nullptr;
	
	auto coverPlaceWithBestScore = CoverSystemController->CoverPlaces[0];
	int bestScore = -999999999;

	OnAdditionalInfoUpdateRequest.Broadcast();
	
	for (auto place : CoverSystemController->CoverPlaces)
	{
		if(place == nullptr) continue;
		if(place->myState != ECoverPlaceState::FREE) continue;
		float distanceToCover = FVector::Distance(GetOwner()->GetActorLocation(),
											  place->GetActorLocation());
		if(distanceToCover<100) continue;// if cover is too close ignore it
		
		int currentCoverScore = 0;
		
		auto TargetInfos = place->GetAllValidTargets();
		for (auto TargetInfo : TargetInfos)
		{
			if(TargetInfo->coverSystemComponent == this) continue;//ignore self
			
			FString* team = TargetInfo->AdditionalInfoMap.Find("TEAM");
			if(team == AdditionalInfo.Find("TEAM")) continue;
				
			
			if(TargetInfo->isTooClose)
				continue;			//this target doesnt affect this place in any way

			if(TargetInfo->isVisionBlocked)	//ignoreTargetIfVisionIsBlocked
				continue;
			
			if(TargetInfo->isInVisibilityRange)
				currentCoverScore+=100/TargetInfo->distance;		//good position because you can shoot others
																	//closer -> better
			
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

ACoverSystemController* UCoverSystemActorComponent::GetCoverSystemController()
{
	UCoverSystemGameInstance* GI = Cast<UCoverSystemGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(GI)
		return Cast<ACoverSystemController>(GI->CoverSystemController.Get());
	else
		return nullptr;
}

// Called every frame
void UCoverSystemActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

