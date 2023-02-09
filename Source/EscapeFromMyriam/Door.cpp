// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorTriggerBox=CreateDefaultSubobject<UBoxComponent>(TEXT("Door Trigger Box"));
	RootComponent=DoorTriggerBox;

	LeftDoor=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Door"));
	LeftDoor->SetupAttachment(DoorTriggerBox);

	RightDoor=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Door"));
	RightDoor->SetupAttachment(DoorTriggerBox);
	

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::OpenDoor()
{	
	if(LeftDoor==nullptr)
	{
		return;
	}

	FRotator CurrentLeftDoorRotation=LeftDoor->GetRelativeRotation();
	FRotator TargetLeftDoorRotation=CurrentLeftDoorRotation + FRotator(0,RotationAmount,0);
	LeftDoor->AddRelativeRotation(FMath::RInterpTo(CurrentLeftDoorRotation,TargetLeftDoorRotation,UGameplayStatics::GetWorldDeltaSeconds(this),RotationSpeed)) ;

	if(RightDoor==nullptr)
	{
		return;
	}

	FRotator CurrentRightDoorRotation=GetActorRotation();
	FRotator TargetRightDoorRotation=CurrentRightDoorRotation + FRotator(0,RotationAmount,0);
	LeftDoor->AddRelativeRotation(FMath::RInterpTo(CurrentRightDoorRotation,TargetRightDoorRotation,UGameplayStatics::GetWorldDeltaSeconds(this),RotationSpeed));
}

void ADoor::CloseDoor()
{
	
}

