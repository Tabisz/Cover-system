


#include "CoverPlace.h"
#include "Kismet/KismetMathLibrary.h"


ACoverPlace::ACoverPlace()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACoverPlace::DrawDebugVisibilityCone(EDirection directionToDraw, float angleDegree, float searchDistance, bool isCovered)
{
	float offsetAngle = 0;
	switch (directionToDraw)
	{
	case EDirection::UP_DIRECTION:
	offsetAngle = 90;
		break;
	case EDirection::DOWN_DIRECTION:
		offsetAngle = -90;
		break;
	case EDirection::LEFT_DIRECTION:
		offsetAngle = 180;
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
		
	
	
	DrawDebugVisibilityLine(angleDegree+offsetAngle, searchDistance, drawColor);

	DrawDebugVisibilityLine(-angleDegree+offsetAngle, searchDistance, drawColor);
	
	DrawDebugVisibilityLine(offsetAngle, searchDistance, FColor::Blue);
}

void ACoverPlace::DrawDebugVisibilityLine(float angleDegree, float Distance, FColor color)
{
	float angleRadians = FMath::DegreesToRadians(angleDegree);
	FVector endPoint =GetActorLocation() + FVector(UKismetMathLibrary::Cos(angleRadians),UKismetMathLibrary::Sin(angleRadians),0)* Distance;
	DrawDebugLine(
			GetWorld(),
			GetActorLocation(),
			endPoint,
			color,
			false, .1f, 0,
			3
		);
}


void ACoverPlace::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
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

