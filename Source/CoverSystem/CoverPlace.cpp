


#include "CoverPlace.h"

#include "CoverSystemGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


ACoverPlace::ACoverPlace()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACoverPlace::BeginPlay()
{
	Super::BeginPlay();

	CoverSystemController = GetCoverSystemController();
	if(!CoverSystemController)
		return;
	CoverSystemController->RegisterNewCover(this);
}

void ACoverPlace::Tick(float DeltaTime)
{

#if WITH_EDITOR
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor)
	{
		BlueprintEditorTick(DeltaTime);
	}
	else
#endif
	{
		Super::Tick(DeltaTime);
		BlueprintEditorTick(DeltaTime);
			
	}
}

void ACoverPlace::ChangeCoverState(ECoverPlaceState newState)
{
	if(myState == newState) return;

	myState = newState;
	//call event state change
		
}

ACoverSystemController* ACoverPlace::GetCoverSystemController() const
{
		UCoverSystemGameInstance* GI = Cast<UCoverSystemGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(GI)
		return Cast<ACoverSystemController>(GI->CoverSystemController.Get());
	else
		return nullptr;
}

TArray<UTargetInfo*> ACoverPlace::GetAllValidTargets()
{
	TArray<UTargetInfo*> targetsInfo = TArray<UTargetInfo*>();
	if(!CoverSystemController)
		return targetsInfo;
	//create target info for all actors
	for (auto coverActor : CoverSystemController->CoverActors)
	{
		if(!coverActor)
			continue;
		UTargetInfo* info;
		info = NewObject<UTargetInfo>();
		info->coverSystemComponent = coverActor;
		
		coverActor->OnAdditionalInfoUpdateRequest.Broadcast();
		info->AdditionalInfoMap = coverActor->AdditionalInfo;
		
		info->distance = CalculateDistance(coverActor);
		info->angle = CalculateAngle(coverActor);
		targetsInfo.Add(info);
	}
	AnalyseTargetsByDistance(targetsInfo);
	AnalyseTargetsByAngle(targetsInfo);

	return targetsInfo;
}

float ACoverPlace::CalculateDistance(UCoverSystemActorComponent* CoverSystemActorComponent)
{
	return FVector::Distance( GetActorLocation(),CoverSystemActorComponent->GetOwner()->GetActorLocation());
}

float ACoverPlace::CalculateAngle(UCoverSystemActorComponent* CoverSystemActorComponent)
{
	FVector directionToTarget = CoverSystemActorComponent->GetOwner()->GetActorLocation() - GetActorLocation();
	directionToTarget.Normalize(.1);
	
	float forwardAngle = FVector::DotProduct(GetActorForwardVector(),directionToTarget);
	forwardAngle = UKismetMathLibrary::DegAcos(forwardAngle);
	
	float rightAngle = FVector::DotProduct(GetActorRightVector(),directionToTarget);
	rightAngle = UKismetMathLibrary::DegAcos(rightAngle);
	if(rightAngle<=90)
		return forwardAngle;
	else
		return 360 - forwardAngle;
}

void ACoverPlace::AnalyseTargetsByDistance(TArray<UTargetInfo*>& actors)
{
	for (int i = actors.Num() - 1; i >= 0; i--)
	{
		if(actors[i]->distance>2000)//set max distance as global variable
		{
			actors.RemoveAt(i);		//remove actor that is too far away
			continue;			
		}
		if(actors[i]->distance<100)//set min distance as global variable
			actors[i]->isTooClose;
	}
}

void ACoverPlace::AnalyseTargetsByAngle(TArray<UTargetInfo*>& targets)
{
	float halfVisibility = 30;
	for (int i = targets.Num() - 1; i >= 0; i--)
	{
		float a = targets[i]->angle;

		if(a >= 360-halfVisibility || a <= halfVisibility)
		{
			targets[i]->isInVisibilityRange = true;
			targets[i]->DirectionToBeVisibleIn = EDirection::FORWARD_DIRECTION;
			if(coverForward)
				targets[i]->isFromCoveredSide = true;
		}
		else if(a >= 90-halfVisibility && a <= 90+halfVisibility)
		{
			targets[i]->isInVisibilityRange = true;
			targets[i]->DirectionToBeVisibleIn = EDirection::RIGHT_DIRECTION;
			if(coverRight)
				targets[i]->isFromCoveredSide = true;
		}
		else if(a >= 180-halfVisibility && a <= 180+halfVisibility)
		{
			targets[i]->isInVisibilityRange = true;
			targets[i]->DirectionToBeVisibleIn = EDirection::BACKWARD_DIRECTION;
			if(coverBackward)
				targets[i]->isFromCoveredSide = true;
		}
		else if(a >= 270-halfVisibility && a <= 270+halfVisibility)
		{
			targets[i]->isInVisibilityRange = true;
			targets[i]->DirectionToBeVisibleIn = EDirection::LEFT_DIRECTION;
			if(coverLeft)
				targets[i]->isFromCoveredSide = true;
		}
		
	}
}
/////////////// DEBUG


// This ultimately is what controls whether or not it can even tick at all in the editor view port. 
//But, it is EVERY view port so it still needs to be blocked from preview windows and junk.
bool ACoverPlace::ShouldTickIfViewportsOnly() const
{
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor && enableDebug)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ACoverPlace::BlueprintEditorTick(float DeltaTime)
{
	if(enableDebug)
		DrawDebug();
}

void ACoverPlace::DrawDebug()
{
	auto targets = GetAllValidTargets();

	bool targetU,targetL,targetD,targetR;
	
	targetU = targetL = targetD = targetR = false;

	for (auto target : targets)
	{
		//DrawDebugLineBetween(target->coverSystemComponent->GetOwner()->GetActorLocation(),FColor::Red);
		if(!target->isInVisibilityRange || target->isTooClose)continue;
		
		targetU = target->DirectionToBeVisibleIn == EDirection::FORWARD_DIRECTION;
		targetD = target->DirectionToBeVisibleIn == EDirection::BACKWARD_DIRECTION;
		targetL = target->DirectionToBeVisibleIn == EDirection::LEFT_DIRECTION;
		targetR = target->DirectionToBeVisibleIn == EDirection::RIGHT_DIRECTION;
	}
		if(visibilityForward)
			DrawDebugVisibilityCone(EDirection::FORWARD_DIRECTION, 30, 2000, coverForward, targetU);
		if(visibilityLeft)
			DrawDebugVisibilityCone(EDirection::LEFT_DIRECTION, 30, 2000, coverLeft, targetL);
		if(visibilityBackward)
			DrawDebugVisibilityCone(EDirection::BACKWARD_DIRECTION, 30, 2000, coverBackward, targetD);
		if(visibilityRight)
			DrawDebugVisibilityCone(EDirection::RIGHT_DIRECTION, 30, 2000, coverRight, targetR);
}

void ACoverPlace::DrawDebugVisibilityCone(EDirection directionToDraw, float visibilityHalfAngle, float searchDistance, bool isCovered, bool discoveredEnemy)
{
	float drawAngle = 0;
	switch (directionToDraw)
	{
	case EDirection::FORWARD_DIRECTION:
		break;
	case EDirection::BACKWARD_DIRECTION:
		drawAngle = FMath::DegreesToRadians(180);
		break;
	case EDirection::LEFT_DIRECTION:
		drawAngle = FMath::DegreesToRadians(-90);
		break;
	case EDirection::RIGHT_DIRECTION:
		drawAngle = FMath::DegreesToRadians(90);
		break;
	default: ;
	}
	FColor drawColor;
	if(discoveredEnemy)
		drawColor = FColor::Red;
	else if(isCovered)
		drawColor = FColor::Yellow;
	else
		drawColor = FColor::Green;

	//DrawDebugVisibilityLine(drawAngle, searchDistance, FColor::Blue);
	
	visibilityHalfAngle = FMath::DegreesToRadians(visibilityHalfAngle);
	
	DrawDebugVisibilityLine(drawAngle+visibilityHalfAngle, searchDistance, drawColor);

	DrawDebugVisibilityLine(drawAngle-visibilityHalfAngle, searchDistance, drawColor);
	
}

void ACoverPlace::DrawDebugVisibilityLine(float drawAngle, float Distance, FColor color)
{
	FVector endPoint =GetActorLocation() +GetActorRotation().RotateVector(FVector(UKismetMathLibrary::Cos(drawAngle),UKismetMathLibrary::Sin(drawAngle),0))* Distance;
	DrawDebugLine(
			GetWorld(),
			GetActorLocation(),
			endPoint,
			color,
			false, .1f, 0,
			3
		);
}

void ACoverPlace::DrawDebugLineBetween(const FVector end,const FColor color) const
{
	DrawDebugLine(
			GetWorld(),
			GetActorLocation(),
			end,
			color,
			false, .1f, 0,
			3
		);
}





