// Fill out your copyright notice in the Description page of Project Settings.


#include "Grapple.h"
#include "Kismet/GameplayStatics.h"
#include "MyriamCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GrappleProjectile.h"


AGrapple::AGrapple()
{

}

void AGrapple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GrappleProjectile && GrappleProjectile->GetIsProjectileComingBack())
	{
		if(GrappleProjectile->GetActorLocation().Equals(GetActorLocation(),20.f))
		{
			GrappleProjectile->Destroy();
			GrappleProjectile=nullptr;
		}
		else
		{
			//set new rotation 
			FVector StartingCallBackLocation = GrappleProjectile->GetActorLocation();
			FVector TargetCallBackLocation = GetActorLocation();
			FRotator CallBackRotation=UKismetMathLibrary::FindLookAtRotation(StartingCallBackLocation, TargetCallBackLocation);
			GrappleProjectile->SetActorRotation(CallBackRotation);

			//Set actor direction
			float ProjectileSpeed=GrappleProjectile->GetProjectileMovementComponent()->GetMaxSpeed();

		

			FVector TargetCallBackDirection=StartingCallBackLocation + (GrappleProjectile->GetActorForwardVector() * ProjectileSpeed * DeltaTime ); 
			GrappleProjectile->SetActorLocation(TargetCallBackDirection);

			
		}
		

	}

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


	//if grapple projectile already exists
	if(GrappleProjectile != nullptr)
	{
		// if it's not attached to a wall, aka if has NOT hit a wall
		if(!(GrappleProjectile->GetHasHit())){
			//call it back, set new direction towards the hand
			//managed in tick
			GrappleProjectile->SetIsProjectileComingBack(true);
			UE_LOG(LogTemp,Warning,TEXT("Call back Grapple"));			

			

		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("Grapple attachet to wall"));	
				//if it's attached to a wall 
			//pull the character to the grapple projectile
		}
	
	}
	else
	{
	//if grapple projectile does not exist spara uno nuovo	
	GrappleProjectile=World->SpawnActor<AGrappleProjectile>(GrappleProjectileClass,GetActorLocation(),Rotation);
	GrappleProjectile->SetIsProjectileComingBack(false);
	}		
    

}
