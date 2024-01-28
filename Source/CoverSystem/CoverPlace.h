// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoverSystemActorComponent.h"
#include "CoverSystemProperties.h"
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

	//Additional info can hold custom info without need of modyfing this class or creating more fields that may not be used
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

	UPROPERTY()
	bool isVisionBlocked;
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
	void ChangeState(ECoverPlaceState NewState);

	
	UFUNCTION(BlueprintCallable)
	void ChangeCoverState(ECoverPlaceState newState);
	
	ACoverSystemController* GetCoverSystemController() const;

	
	UFUNCTION(BlueprintCallable)
	TArray<UTargetInfo*> GetAllValidTargets();
	
	float CalculateDistance(UCoverSystemActorComponent* CoverSystemActorComponent);

	float CalculateAngle(UCoverSystemActorComponent* CoverSystemActorComponent);
	
	void AnalyseTargetsByDistance(TArray<UTargetInfo*>& actors);

	void AnalyseTargetsByAngle(TArray<UTargetInfo*>& targets);

	void AnalyseBlockingVisibility(TArray<UTargetInfo*>& targets);


	//toggle these if you want to enable actor to shoot in direction
	UPROPERTY(EditAnywhere, Category="Visibility")
	bool visibilityRight = true;
	UPROPERTY(EditAnywhere, Category="Visibility")
	bool visibilityLeft;
	UPROPERTY(EditAnywhere, Category="Visibility")
	bool visibilityForward;
	UPROPERTY(EditAnywhere, Category="Visibility")
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

	UPROPERTY(EditAnywhere, Category="Debug")
	UCoverSystemProperties* DEBUG_SystemProperties;

	/** Allows Tick To happen in the editor viewport*/
	virtual bool ShouldTickIfViewportsOnly() const override;

	/** Tick that runs ONLY in the editor viewport.*/
	UFUNCTION()
	void BlueprintEditorTick(float DeltaTime);

	
	UFUNCTION(Category="Debug")
	void DrawDebug();
	
	UFUNCTION(BlueprintCallable, Category="Debug")
	void DrawDebugVisibilityCone(EDirection directionToDraw, bool isCovered, bool discoveredEnemy);
	
	UFUNCTION(BlueprintCallable, Category="Debug")
	void DrawDebugVisibilityLine(float drawAngle, float Distance, FColor color);
	
	void DrawDebugLineBetween(const FVector end,const FColor color) const;

};
