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
	//Se é chiusa
	if(!bIsOpen)
	{	
		//apri porta sinistra
		if(LeftDoor!=nullptr)
		{			
			//UE_LOG(LogTemp,Warning,TEXT("Si! é una porta! Apriti!"));
			FRotator CurrentLeftDoorRotation=LeftDoor->GetRelativeRotation();
			FRotator TargetLeftDoorRotation=CurrentLeftDoorRotation + FRotator(0,RotationAmount,0);
			LeftDoor->SetRelativeRotation(TargetLeftDoorRotation) ;
		}
		//apri porta destra
		if(RightDoor!=nullptr)
		{
			//UE_LOG(LogTemp,Warning,TEXT("Si! é una porta! Apriti!"));
			FRotator CurrentRightDoorRotation=RightDoor->GetRelativeRotation();
			FRotator TargetRightDoorRotation=CurrentRightDoorRotation + FRotator(0,RotationAmount,0);
			RightDoor->SetRelativeRotation(TargetRightDoorRotation);
		}

	}
	//se é aperta
	else
	{
		//chiudi porta sinistra
		if(LeftDoor!=nullptr)
		{			
			//UE_LOG(LogTemp,Warning,TEXT("Chiudi"));
			FRotator CurrentLeftDoorRotation=LeftDoor->GetRelativeRotation();
			FRotator TargetLeftDoorRotation=CurrentLeftDoorRotation + FRotator(0,-RotationAmount,0);
			LeftDoor->SetRelativeRotation(TargetLeftDoorRotation) ;
			
		}
		//chiudi porta destra
		if(RightDoor!=nullptr)
		{
			//UE_LOG(LogTemp,Warning,TEXT("Chiudi"));
			FRotator CurrentRightDoorRotation=RightDoor->GetRelativeRotation();
			FRotator TargetRightDoorRotation=CurrentRightDoorRotation + FRotator(0,-RotationAmount,0);
			RightDoor->SetRelativeRotation(TargetRightDoorRotation);
		}

	}
}

void ADoor::SetIsOpenDoor(bool IsOpen)
{
	bIsOpen=IsOpen;
}

bool ADoor::GetIsOpenDoor()
{
	return bIsOpen;
}

