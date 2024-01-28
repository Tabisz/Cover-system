// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CoverSystemActorComponent.generated.h"

class ACoverSystemController;
class ACoverPlace;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRequestAdditionalInfo);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COVERSYSTEM_API UCoverSystemActorComponent : public UActorComponent
{
	GENERATED_BODY()



public:	
	// Sets default values for this component's properties
	UCoverSystemActorComponent();

	FInit OnRegisterCompleted;
	FRequestAdditionalInfo OnAdditionalInfoUpdateRequest;

	UPROPERTY(BlueprintReadOnly)
	ACoverSystemController* CoverSystemController;

	UPROPERTY(BlueprintReadWrite)
	ACoverPlace* OccupiedCoverPlace;
	
	UPROPERTY(BlueprintReadWrite)
	ACoverPlace* RegisteredCoverPlace;


	UFUNCTION(BlueprintCallable)
	void FreeUpCoverPlace(); 
	
	UFUNCTION(BlueprintCallable)
	bool RegisterCoverPlace(ACoverPlace* coverPlace);

	UFUNCTION(BlueprintCallable)
	bool OccupyRegisteredCoverPlace(); 

	UPROPERTY(BlueprintReadWrite)
	TMap<FKey, FString> AdditionalInfo;

	UFUNCTION(BlueprintCallable)
	ACoverPlace* GetBestCoverPlace();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	ACoverSystemController* GetCoverSystemController();
	

	

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
