// Fill out your copyright notice in the Description page of Project Settings.


#include "InteactableKey.h"
#include "MyriamCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteactableKey::AInteactableKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteactableKey::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteactableKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AInteactableKey::BeginOverlapInteraction(AActor* OtherActor)
{

}

void AInteactableKey::EndOverlapInteraction(AActor* OtherActor)
{

}

void AInteactableKey::Interact(AActor* OtherActor)
{
	if(OtherActor==nullptr)
	{
		return;
	}

	bool bHasInterface=OtherActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass());

	if(bHasInterface)
	{
		
		AMyriamCharacter* OtherMyriamActor = Cast<AMyriamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
		UE_LOG(LogTemp,Warning,TEXT("aggiungi a inventario"));	
		
		OtherMyriamActor->AddItemToInventory("Key");	
		this->Destroy();
	}

}
