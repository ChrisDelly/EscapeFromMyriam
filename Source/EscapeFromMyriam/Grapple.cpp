// Fill out your copyright notice in the Description page of Project Settings.


#include "Grapple.h"
#include "Kismet/GameplayStatics.h"
#include "MyriamCharacter.h"
#include "GrappleProjectile.h"


AGrapple::AGrapple()
{

}

void AGrapple::ToolActivate() 
{
    Super::ToolActivate();
    UE_LOG(LogTemp,Warning,TEXT("Grapple Action"));

	UWorld* World=GetWorld();

	if(World == nullptr)
	{
		return;	
	}

    AMyriamCharacter* Player = Cast<AMyriamCharacter>(UGameplayStatics::GetPlayerPawn(World,0));
    AController* OwnerController=Player->GetController();
	if(OwnerController == nullptr) 
	    return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint( Location, Rotation );

	GrappleProjectile=World->SpawnActor<AGrappleProjectile>(GrappleProjectileClass,GetActorLocation(),Rotation);
    
    

}
