// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool.h"

// Sets default values
ATool::ATool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATool::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ATool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATool::ToolActivate()
{
    //UE_LOG(LogTemp,Warning,TEXT("tool Action"));
	
}

