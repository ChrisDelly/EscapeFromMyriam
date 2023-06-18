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

	if(GrappleProjectile)
	{
		if(GrappleProjectile->GetIsProjectileComingBack())
		{
			if(GrappleProjectile->GetActorLocation().Equals(GetActorLocation(),40.f))
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
				FVector ProjectileForwardVector =GrappleProjectile->GetActorForwardVector();
				float ProjectileSpeed=GrappleProjectile->GetProjectileMovementComponent()->GetMaxSpeed();
			

				FVector TargetCallBackDirection=StartingCallBackLocation + (ProjectileForwardVector * ProjectileSpeed * DeltaTime ); 
				UE_LOG(LogTemp,Warning,TEXT("Vettore direzione di ritorno %s"),*ProjectileForwardVector.ToString());

				GrappleProjectile->SetActorLocation(TargetCallBackDirection);

				
			}
			

		}
		else
		{
			//Set actor direction
			FVector StartingLocation = GrappleProjectile->GetActorLocation();
			FVector ProjectileForwardVector =GrappleProjectile->GetActorForwardVector();
			float ProjectileSpeed=GrappleProjectile->GetProjectileMovementComponent()->GetMaxSpeed();		

			FVector TargetCallBackDirection=StartingLocation + (ProjectileForwardVector * ProjectileSpeed * DeltaTime ); 

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

	GrappleProjectile->SetOwner(this);
	GrappleProjectile->SetIsProjectileComingBack(false);
	}		
    

}
