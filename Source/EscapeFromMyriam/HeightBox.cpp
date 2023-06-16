// Fill out your copyright notice in the Description page of Project Settings.


#include "HeightBox.h"


void AHeightBox::ToolActivate()
{
	Super::ToolActivate();
    UE_LOG(LogTemp,Warning,TEXT("Height Box Action"));


    /*TO DO develop logic for heightbox, the following code is to be reused and rearranged for this task
	if(ObjectsToDropClass.IsEmpty())
	{
		return;
	}
	
	UWorld* World=GetWorld();
	if(World == nullptr)
	{
		return;
	}

	FTransform SpawnTransform = GetActorTransform();
	
	ObjectToDropIndex=FMath::RandRange(0,ObjectsToDropClass.Num()-1);
	
	auto SpawnedObject = World->SpawnActor<AActor>(ObjectsToDropClass[ObjectToDropIndex],ObjectSpawnPoint->GetComponentLocation(),ObjectSpawnPoint->GetComponentRotation());

    */
	
}
