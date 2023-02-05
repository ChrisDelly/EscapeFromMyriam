// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult HitResult;
	FVector LineStartLocation=GetComponentLocation();
	FVector LineEndLocation= LineStartLocation + GetForwardVector() * MaxGrabDistance;
	bool HasHit=GetWorld()->SweepSingleByChannel(HitResult,
	LineStartLocation,
	LineEndLocation,
	FQuat::Identity,
	ECC_GameTraceChannel1,
	FCollisionShape::MakeSphere(SweepSize)
	);

	//DrawDebugLine(GetWorld(),LineStartLocation,LineEndLocation,FColor::Red,false,10,1,20);

	if(HasHit)
	{
		AActor* hitactor=HitResult.GetActor();
		UE_LOG(LogTemp,Warning,TEXT("Hit! %s"),*hitactor->GetActorNameOrLabel());
	}
	
}

