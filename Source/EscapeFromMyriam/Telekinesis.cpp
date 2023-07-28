// Fill out your copyright notice in the Description page of Project Settings.


#include "Telekinesis.h"
#include "Kismet/GameplayStatics.h"
#include "MyriamCharacter.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"


ATelekinesis::ATelekinesis()
{
    TelekinesisMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Telekinesis Mesh"));
	RootComponent=TelekinesisMesh;
}

void ATelekinesis::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    ManageLineTraceTelekinesis();    
    
}

void ATelekinesis::ToolActivate()
{
    AMyriamCharacter* Player=Cast<AMyriamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

    if(Player == nullptr)
        return;
    
    ObjectToGrab=HitComponent;
    //If grab is active release the object/actor currently grabbed
    if(IsGrabActive)
    {
        IsGrabActive = false;
        
        UE_LOG(LogTemp,Warning,TEXT("Release"));

        UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();        
        if(PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
        {
            PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();		
            PhysicsHandle->ReleaseComponent();
        }
        //Launch grabbed object
        if(HitComponent)
        {
            HitComponent->AddImpulse(Player->GetCamera()->GetForwardVector()*LaunchForce,NAME_None,true);
        }
        


        ObjectToGrab=nullptr;
    }
    else
    {
         //if the object/actor can be grabbed, grab it       
        if (ObjectToGrab == nullptr)
        {
            UE_LOG(LogTemp,Warning,TEXT("Can't grab"));    
            return;
        }
        else 
        {                   
            IsGrabActive = true;
            UE_LOG(LogTemp,Warning,TEXT("Grab component %s"),*ObjectToGrab->GetName() );  

            UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
            if(PhysicsHandle==nullptr) return;                    

            if (HitComponent && HitActor)
                {                    
                    HitComponent->SetSimulatePhysics(true);
                    HitComponent->WakeAllRigidBodies();
                    HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
                    PhysicsHandle->GrabComponentAtLocationWithRotation(
                        HitComponent,
                        NAME_None,
                        HitActor->GetActorLocation(),
                        Player->GetActorRotation()
                    );
                }        
        }        
    }
}


UPhysicsHandleComponent* ATelekinesis::GetPhysicsHandle() const
{
  UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if(Result==nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber Requires a UPhysicsHandleComponent"));
	}	
		return Result;

}

void ATelekinesis::ManageLineTraceTelekinesis()
{
    AMyriamCharacter* Player=Cast<AMyriamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));   

    //line trace
    FHitResult HitResult;
	FVector LineStartLocation=Player->GetActorLocation();
	FVector LineEndLocation= LineStartLocation + Player->GetCamera()->GetForwardVector() * MaxGrabDistance;
	bool HasHit=GetWorld()->SweepSingleByChannel(HitResult,
	LineStartLocation,
	LineEndLocation,
	FQuat::Identity,
	ECC_GameTraceChannel2,
	FCollisionShape::MakeSphere(GrabRadius)
	);

    //DrawDebugSphere(GetWorld(),HitResult.Location,20,12,FColor::Red,false,2);

	if(HasHit)
	{
		HitActor=HitResult.GetActor();
		HitComponent=HitResult.GetComponent();
	}
	else
	{
		HitActor=nullptr;
		HitComponent=nullptr;
	}

    //physics
    UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();	
	
	if(PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation=Player->GetActorLocation() + Player->GetCamera()->GetForwardVector() *HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation,Player->GetActorRotation());
	}

}