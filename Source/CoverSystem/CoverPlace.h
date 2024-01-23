// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "CoverPlace.generated.h"

UENUM()
enum class EDirection : uint8
{
	DOWN_DIRECTION,  
	LEFT_DIRECTION,
	UP_DIRECTION,
	RIGHT_DIRECTION
};

ENUM_CLASS_FLAGS(EDirection);


UCLASS()
class COVERSYSTEM_API ACoverPlace : public AActor
{
	GENERATED_BODY()
	
public:	
	ACoverPlace();

	UFUNCTION(BlueprintCallable)
	void GetAllValiableTargets();

	UFUNCTION(BlueprintCallable)
	void FilterTargetsByDistance();

	UFUNCTION(BlueprintCallable)
	void FilterTargetsByAngles();
	
	
	
	// UFUNCTION(BlueprintCallable, Category="Debug")
	// void DrawDebugLineBetween(FVector start, FVector End, FColor color);
	
	UFUNCTION(BlueprintCallable, Category="Debug")
	void DrawDebugVisibilityCone(EDirection directionToDraw, float visibilityHalfAngle, float searchDistance, bool isCovered);
	
	UFUNCTION(BlueprintCallable, Category="Debug")
	void DrawDebugVisibilityLine(float drawAngle, float Distance, FColor color);
	
	UPROPERTY(EditAnywhere, Category="Debug")
	bool drawRight = true;
	UPROPERTY(EditAnywhere, Category="Debug")
	bool drawLeft;
	UPROPERTY(EditAnywhere, Category="Debug")
	bool drawUp;
	UPROPERTY(EditAnywhere, Category="Debug")
	bool drawDown;

	UPROPERTY(EditAnywhere, Category="Cover")
	bool coverRight = true;
	UPROPERTY(EditAnywhere, Category="Cover")
	bool coverLeft;
	UPROPERTY(EditAnywhere, Category="Cover")
	bool coverUp;
	UPROPERTY(EditAnywhere, Category="Cover")
	bool coverDown;


public:	
	virtual void Tick(float DeltaTime) override;

};
