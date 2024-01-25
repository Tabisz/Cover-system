


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
	Super::Tick(DeltaTime);

	auto targets = GetAllValidTargets();

	bool targetU,targetL,targetD,targetR;
	for (auto target : targets)
	{
		DrawDebugLineBetween(target->coverSystemComponent->GetOwner()->GetActorLocation(),FColor::Red);
			targetU = target->DirectionToBeVisibleIn == EDirection::FORWARD_DIRECTION;
		targetD = target->DirectionToBeVisibleIn == EDirection::BACKWARD_DIRECTION;
		targetL = target->DirectionToBeVisibleIn == EDirection::LEFT_DIRECTION;
		targetR = target->DirectionToBeVisibleIn == EDirection::RIGHT_DIRECTION;

		
	}
	
	if(drawUp)
		DrawDebugVisibilityCone(EDirection::FORWARD_DIRECTION, 30, 1000, coverUp, targetU);
	if(drawLeft)
		DrawDebugVisibilityCone(EDirection::LEFT_DIRECTION, 30, 1000, coverLeft, targetL);
	if(drawDown)
		DrawDebugVisibilityCone(EDirection::BACKWARD_DIRECTION, 30, 1000, coverDown, targetD);
	if(drawRight)
		DrawDebugVisibilityCone(EDirection::RIGHT_DIRECTION, 30, 1000, coverRight, targetR);

	
	
}

ACoverSystemController* ACoverPlace::GetCoverSystemController()
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

void ACoverPlace::AnalyseTargetsByAngle(TArray<UTargetInfo*>& actors)
{
	float halfVisibility = 30;
	for (int i = actors.Num() - 1; i >= 0; i--)
	{
		float a = actors[i]->angle;

		if(a >= 360-halfVisibility || a <= halfVisibility)
		{
			actors[i]->isInVisibilityRange = true;
			actors[i]->DirectionToBeVisibleIn = EDirection::FORWARD_DIRECTION;
		}
		else if(a >= 90-halfVisibility && a <= 90+halfVisibility)
		{
			actors[i]->isInVisibilityRange = true;
			actors[i]->DirectionToBeVisibleIn = EDirection::RIGHT_DIRECTION;
		}
		else if(a >= 180-halfVisibility && a <= 180+halfVisibility)
		{
			actors[i]->isInVisibilityRange = true;
			actors[i]->DirectionToBeVisibleIn = EDirection::BACKWARD_DIRECTION;
		}
		else if(a >= 270-halfVisibility && a <= 270+halfVisibility)
		{
			actors[i]->isInVisibilityRange = true;
			actors[i]->DirectionToBeVisibleIn = EDirection::LEFT_DIRECTION;
		}
		
	}
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
		
		//default
		break;
	default: ;
	}
	FColor drawColor;
	if(isCovered)
		drawColor = FColor::Yellow;
	else if(discoveredEnemy)
		drawColor = FColor::Red;
	else
		drawColor = FColor::Green;

	//drawAngle += forwardAngle;
	DrawDebugVisibilityLine(drawAngle, searchDistance, FColor::Blue);
	
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





