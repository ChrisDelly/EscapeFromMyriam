// Fill out your copyright notice in the Description page of Project Settings.


#include "WinningTriggerVolume.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "MyriamCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWinningTriggerVolume::AWinningTriggerVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WinVolume=CreateDefaultSubobject<UBoxComponent>(TEXT("Win Trigger Box"));
	RootComponent=WinVolume;

	WinVolume->OnComponentBeginOverlap.AddUniqueDynamic(this,&AWinningTriggerVolume::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AWinningTriggerVolume::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void AWinningTriggerVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWinningTriggerVolume::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if(IsValid(WinningWidgetClass) && OtherActor->IsA(AMyriamCharacter::StaticClass()))
	{
		WinningScreen=CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(),0),WinningWidgetClass);
		if(WinningScreen!=nullptr)
		{
			WinningScreen->AddToViewport();
		}
	}
}

