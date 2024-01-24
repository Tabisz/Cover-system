

#include "CoverSystemActorComponent.h"

#include "CoverSystemGameInstance.h"
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

