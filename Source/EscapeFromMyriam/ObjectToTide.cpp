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

