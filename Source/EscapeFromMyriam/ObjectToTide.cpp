// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectToTide.h"

// Sets default values
AObjectToTide::AObjectToTide()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObjectToTide::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjectToTide::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AObjectToTide::GetIsInOrder()
{
	return bIsInOrder;
}

void AObjectToTide::SetIsInOrder(bool InOrder)
{
	bIsInOrder=InOrder;
}

void AObjectToTide::BeginOverlapInteraction(AActor* OtherActor)
{

}

void AObjectToTide::EndOverlapInteraction(AActor* OtherActor)
{

}

void AObjectToTide::Interact(AActor* OtherActor)
{
	if(OtherActor==nullptr)
	{
		return;
	}

	bool bHasInterface=OtherActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass());

	if(bHasInterface)
	{
		//AObjectToTide* OTT= Cast<AObjectToTide>(OtherActor);
		//IInteractInterface::Execute_Interact(OtherActor);
		UE_LOG(LogTemp,Warning,TEXT("object to tide interact implementation"));
		SetIsInOrder(false);
	}

	
}


