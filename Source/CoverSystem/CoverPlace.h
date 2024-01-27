// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoverSystemActorComponent.h"
#include "GameFramework/Actor.h"
#include "CoverPlace.generated.h"

UENUM(BlueprintType)
enum class EDirection : uint8
{
	BACKWARD_DIRECTION,  
	LEFT_DIRECTION,
	FORWARD_DIRECTION,
	RIGHT_DIRECTION
};

UENUM(BlueprintType)
enum class ECoverPlaceState : uint8
{
	FREE,  
	REGISTERED,
	OCCUPIED
};

UCLASS()
class COVERSYSTEM_API UTargetInfo : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UCoverSystemActorComponent* coverSystemComponent;

	UPROPERTY()
	TMap<FKey, FString> AdditionalInfoMap;
	
	UPROPERTY()
	float angle;

	UPROPERTY()
	float distance;

	UPROPERTY()
	EDirection DirectionToBeVisibleIn;

	UPROPERTY()
	bool isTooClose;

	UPROPERTY()
	bool isInVisibilityRange;

	UPROPERTY()
	bool isAbleToSeeYou;
	
	UPROPERTY()
	bool isFromCoveredSide;
	
};


ENUM_CLASS_FLAGS(EDirection);

class ACoverSystemController;

UCLASS()
class COVERSYSTEM_API ACoverPlace : public AActor
{
	GENERATED_BODY()
	
public:	
	ACoverPlace();

		
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	ACoverSystemController* CoverSystemController;

	UPROPERTY(BlueprintReadWrite)
	ECoverPlaceState myState;

	
	UFUNCTION(BlueprintCallable)
	void ChangeCoverState(ECoverPlaceState newState);
	
	ACoverSystemController* GetCoverSystemController() const;

	
	UFUNCTION(BlueprintCallable)
	TArray<UTargetInfo*> GetAllValidTargets();
	
	float CalculateDistance(UCoverSystemActorComponent* CoverSystemActorComponent);

	float CalculateAngle(UCoverSystemActorComponent* CoverSystemActorComponent);
	UFUNCTION(BlueprintCallable)
	void AnalyseTargetsByDistance(TArray<UTargetInfo*>& actors);

	UFUNCTION(BlueprintCallable)
	void AnalyseTargetsByAngle(TArray<UTargetInfo*>& targets);
	
	UPROPERTY(EditAnywhere, Category="Cover")
	bool visibilityRight = true;
	UPROPERTY(EditAnywhere, Category="Cover")
	bool visibilityLeft;
	UPROPERTY(EditAnywhere, Category="Cover")
	bool visibilityForward;
	UPROPERTY(EditAnywhere, Category="Cover")
	bool visibilityBackward;

	UPROPERTY(EditAnywhere, Category="Cover")
	bool coverRight = true;
	UPROPERTY(EditAnywhere, Category="Cover")
	bool coverLeft;
	UPROPERTY(EditAnywhere, Category="Cover")
	bool coverForward;
	UPROPERTY(EditAnywhere, Category="Cover")
	bool coverBackward;


	
	UPROPERTY(EditAnywhere, Category="Debug")
	bool enableDebug;

	/** Allows Tick To happen in the editor viewport*/
	virtual bool ShouldTickIfViewportsOnly() const override;

	/** Tick that runs ONLY in the editor viewport.*/
	UFUNCTION()
	void BlueprintEditorTick(float DeltaTime);

	
	UFUNCTION(Category="Debug")
	void DrawDebug();
	
	UFUNCTION(BlueprintCallable, Category="Debug")
	void DrawDebugVisibilityCone(EDirection directionToDraw, float visibilityHalfAngle, float searchDistance, bool isCovered, bool discoveredEnemy);
	
	UFUNCTION(BlueprintCallable, Category="Debug")
	void DrawDebugVisibilityLine(float drawAngle, float Distance, FColor color);
	
	void DrawDebugLineBetween(const FVector end,const FColor color) const;

};
