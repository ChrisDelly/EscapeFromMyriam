// Fill out your copyright notice in the Description page of Project Settings.


#include "Grapple.h"
#include "Kismet/GameplayStatics.h"
#include "MyriamCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GrappleProjectile.h"


AGrapple::AGrapple()
{

}

void AGrapple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//mangage grapple coming back
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

	//manage character boing pulled towards grapple
	if(IsCharacterBeingPulledToGrapple)
	{
		
   		UE_LOG(LogTemp,Warning,TEXT("Pulling"));
		AMyriamCharacter* Player = Cast<AMyriamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
		if(Player  == nullptr)
			return;		
		if(!GrappleProjectile)
			return;
		
		FVector StartingLocation=Player->GetActorLocation();

		if(StartingLocation.Equals(GrappleProjectile->GetActorLocation(),100))
		{
			APlayerController* PlayerController=GetWorld()->GetFirstPlayerController();
			if(PlayerController)
			{
				Player->EnableInput(PlayerController);
				Player->GetMovementComponent()->SetMovementMode(EMovementMode::MOVE_Walking);
			}
			IsCharacterBeingPulledToGrapple=false;
			GrappleProjectile->Destroy();
			GrappleProjectile=nullptr;
			return;
			
		}

		FVector DirectionToTarget=GrappleProjectile->GetActorLocation()-StartingLocation;
		DirectionToTarget.Normalize();
		FVector TargetLocation= StartingLocation + (DirectionToTarget * CharacterPullSpeed * DeltaTime);
		Player->SetActorLocation(TargetLocation);
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
	if(Player  == nullptr)
		return;
    AController* OwnerController=Player->GetController();
	if(OwnerController == nullptr) 
	    return;

	FVector Location;
	FRotator Rotation;

	//shooting direction where thw player is looking
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
			UE_LOG(LogTemp,Warning,TEXT("Grapple attached to wall"));	
			//if it's attached to a wall 
			//pull the character to the grapple projectile
			//managed movement in tick
			IsCharacterBeingPulledToGrapple=true;
			APlayerController* PlayerController=GetWorld()->GetFirstPlayerController();
			if(PlayerController)
			{
				Player->DisableInput(PlayerController);
				Player->GetMovementComponent()->SetMovementMode(EMovementMode::MOVE_Flying);
			}
				
				

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
