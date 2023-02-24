// Fill out your copyright notice in the Description page of Project Settings.


#include "HidingPlace.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AHidingPlace::AHidingPlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComponent=CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Trigger"));
	RootComponent=SphereComponent;

	InsideHidingLocation=CreateDefaultSubobject<USceneComponent>(TEXT("Inside Hiding Location"));
	InsideHidingLocation->SetupAttachment(RootComponent);

	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	VisibilityMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visibility Mesh"));
	VisibilityMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHidingPlace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHidingPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHidingPlace::BeginOverlapInteraction(AActor* OtherActor)
{
	
}

void AHidingPlace::EndOverlapInteraction(AActor* OtherActor)
{
	
}

void AHidingPlace::Interact(AActor* OtherActor)
{
	UE_LOG(LogTemp,Warning,TEXT("HidingPlace interact"));
}

