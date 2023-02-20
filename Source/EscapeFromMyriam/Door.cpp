// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "MyriamCharacter.h"
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
	if(LeftDoor!=nullptr)
		{			
			UE_LOG(LogTemp,Warning,TEXT("Si! é una porta! Apriti!"));
			FRotator CurrentLeftDoorRotation=LeftDoor->GetRelativeRotation();
			FRotator TargetLeftDoorRotation=CurrentLeftDoorRotation + FRotator(0,RotationAmount,0);
			LeftDoor->SetRelativeRotation(TargetLeftDoorRotation) ;
		}
}

void ADoor::CloseDoor()
{
	if(LeftDoor!=nullptr)
		{			
			UE_LOG(LogTemp,Warning,TEXT("Chiudi"));
			FRotator CurrentLeftDoorRotation=LeftDoor->GetRelativeRotation();
			FRotator TargetLeftDoorRotation=CurrentLeftDoorRotation + FRotator(0,-RotationAmount,0);
			LeftDoor->SetRelativeRotation(TargetLeftDoorRotation) ;			
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



void ADoor::BeginOverlapInteraction(AActor* OtherActor)
{

}

void ADoor::EndOverlapInteraction(AActor* OtherActor)
{

}

void ADoor::Interact(AActor* OtherActor)
{
	if(OtherActor==nullptr)
	{
		return;
	}

	bool bHasInterface=OtherActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass());

	if(bHasInterface)
	{	
		if(this->ActorHasTag("Door"))
		{				
			UE_LOG(LogTemp,Warning,TEXT("Door"));
			OpenOrCloseDoor();
		}		


		if(this->ActorHasTag("DoorWithKey"))
		{	
			//check has key	to Open
		UE_LOG(LogTemp,Warning,TEXT("Door WITH KEY"));	

		AMyriamCharacter* OtherMyriamActor = Cast<AMyriamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

		if(OtherMyriamActor->GetInventory().Contains<FString>("Key"))
		{
			OpenOrCloseDoor();
		}
			
		}
			
	}

	
}

void ADoor::OpenOrCloseDoor()
{
	//Se aperta
		if(GetIsOpenDoor())
			{
				UE_LOG(LogTemp,Warning,TEXT("ApertaDaChiudere"));
				//chiudi
				CloseDoor();
				SetIsOpenDoor(false);
				
			}
			else
			//se chiusa
			{	
				//apri
				UE_LOG(LogTemp,Warning,TEXT("ChiusaDaAprire"));
				OpenDoor();
				SetIsOpenDoor(true);
			}
}
