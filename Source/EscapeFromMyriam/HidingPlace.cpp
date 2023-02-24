// Fill out your copyright notice in the Description page of Project Settings.


#include "HidingPlace.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "MyriamCharacter.h"
#include "MyriamPlayerController.h"
#include "Kismet/GameplayStatics.h"

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
	
	AMyriamCharacter* MyriamPlayer = Cast<AMyriamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	APlayerController* MyriamController= UGameplayStatics::GetPlayerController(GetWorld(),0);

	

	//Set player location and rotation inside the spot Location
	if(!bIsHidden)
	{
		//location before hiding, will be useful later by exiting the hiding spot
		OutsideLocation=MyriamPlayer->GetActorLocation();
		OutsideRotation=MyriamController->GetControlRotation();

		MyriamPlayer->SetActorLocation(InsideHidingLocation->GetComponentLocation());
		MyriamController->SetControlRotation(InsideHidingLocation->GetComponentRotation());
	
		//MyriamController->SetViewTarget(MyriamPlayer->GetFirstPersonCamera());

		bIsHidden=true;
	}
	else
	{
		MyriamPlayer->SetActorLocation(OutsideLocation);
		MyriamController->SetControlRotation(OutsideRotation);

		//MyriamController->SetViewTarget(MyriamPlayer->GetFirstPersonCamera());

		bIsHidden=false;
	}



	UE_LOG(LogTemp,Warning,TEXT("HidingPlace interact from"));
}

