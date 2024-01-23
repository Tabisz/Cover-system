


#include "CoverPlace.h"
#include "Kismet/KismetMathLibrary.h"


ACoverPlace::ACoverPlace()
{
	PrimaryActorTick.bCanEverTick = true;
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
}

void ACoverPlace::GetAllValiableTargets()
{
	//take all actors
	//fiter them by max and min distance
	FilterTargetsByDistance();
	//filter them by angles
	FilterTargetsByAngles();

	//return targets
}

void ACoverPlace::FilterTargetsByDistance()
{
}

void ACoverPlace::FilterTargetsByAngles()
{
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



