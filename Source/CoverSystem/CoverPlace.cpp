


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
	
	if(drawUp)
		DrawDebugVisibilityCone(EDirection::UP_DIRECTION, 30, 1000, coverUp);
	if(drawLeft)
		DrawDebugVisibilityCone(EDirection::LEFT_DIRECTION, 30, 1000, coverLeft);
	if(drawDown)
		DrawDebugVisibilityCone(EDirection::DOWN_DIRECTION, 30, 1000, coverDown);
	if(drawRight)
		DrawDebugVisibilityCone(EDirection::RIGHT_DIRECTION, 30, 1000, coverRight);

	auto targets = GetAllValidTargets();
	for (auto target : targets)
	{
		DrawDebugLineBetween(target->GetOwner()->GetActorLocation(),FColor::Red);
	}
}

ACoverSystemController* ACoverPlace::GetCoverSystemController()
{
		UCoverSystemGameInstance* GI = Cast<UCoverSystemGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(GI)
		return Cast<ACoverSystemController>(GI->CoverSystemController.Get());
	else
		return nullptr;
}

TArray<UCoverSystemActorComponent*> ACoverPlace::GetAllValidTargets()
{
		TArray<UCoverSystemActorComponent*> localCoverActors;
	if(!CoverSystemController) return localCoverActors;
	//take all actors
	localCoverActors = CoverSystemController->CoverActors;
	//fiter them by max and min distance
	FilterTargetsByDistance(localCoverActors);

	return localCoverActors;
}

void ACoverPlace::FilterTargetsByDistance(TArray<UCoverSystemActorComponent*>& actors)
{
	FVector myLocation = GetActorLocation();
	FVector otherLocation;
	float distance;
	for (int i = actors.Num() - 1; i >= 0; i--)
	{
		otherLocation = actors[i]->GetOwner()->GetActorLocation();
		distance = FVector::Distance(myLocation,otherLocation);
		if(distance<100 || distance>2000)
			actors.RemoveAt(i);
	}
}

void ACoverPlace::FilterTargetsByAngles(TArray<UCoverSystemActorComponent*>& actors)
{
	//TODO
}

void ACoverPlace::DrawDebugVisibilityCone(EDirection directionToDraw, float visibilityHalfAngle, float searchDistance, bool isCovered)
{
	float drawAngle = 0;
	switch (directionToDraw)
	{
	case EDirection::UP_DIRECTION:
		drawAngle = FMath::DegreesToRadians(90);
		break;
	case EDirection::DOWN_DIRECTION:
		drawAngle = FMath::DegreesToRadians(-90);
		break;
	case EDirection::LEFT_DIRECTION:
		drawAngle = FMath::DegreesToRadians(180);
		break;
	case EDirection::RIGHT_DIRECTION:
		//default
		break;
	default: ;
	}
	FColor drawColor;
	if(isCovered)
		drawColor = FColor::Yellow;
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





