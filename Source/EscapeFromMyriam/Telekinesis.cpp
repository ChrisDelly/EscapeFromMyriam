// Fill out your copyright notice in the Description page of Project Settings.


#include "Telekinesis.h"
#include "Kismet/GameplayStatics.h"
#include "MyriamCharacter.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
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

    //if(Player == nullptr)
    //    return;
    
    ObjectToGrab=HitComponent;
    //If grab is active release the object/actor currently grabbed
    if(IsGrabActive)
    {
        IsGrabActive = false;
        ObjectToGrab=nullptr;
        UE_LOG(LogTemp,Warning,TEXT("Release"));

        UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();        
        if(PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
        {
            PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();		
            PhysicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
            PhysicsHandle->ReleaseComponent();
        }
    }
    else
    {
         //if the object/actor can be grabbed, grab it
       
        if (ObjectToGrab == nullptr)
        {
            UE_LOG(LogTemp,Warning,TEXT("Can't grab"));    
            return;
        }else 
        //if  (ObjectToGrab->ComponentHasTag(TEXT("Grabbable")))
        {                   
            IsGrabActive = true;
            UE_LOG(LogTemp,Warning,TEXT("componente %s"),*ObjectToGrab->GetName() );   
            UE_LOG(LogTemp,Warning,TEXT("Grab"));

            UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
            if(PhysicsHandle==nullptr) return;
                    
        //FHitResult HitResult;
        //bool HasHit = GetGrabbableInReach(HitResult);

        if (HitComponent && HitActor)
            {
                //UPrimitiveComponent* HittedComponent=HitResult.GetComponent();
                HitComponent->SetSimulatePhysics(true);
                HitComponent->WakeAllRigidBodies();

                HitActor->Tags.Add("Grabbed");
                HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
                PhysicsHandle->GrabComponentAtLocationWithRotation(
                    HitComponent,
                    NAME_None,
                    HitActor->GetActorLocation(),
                    GetActorRotation()
                );
            }else
            {
            //UE_LOG(LogTemp, Warning, TEXT("no Hit Actor"));
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


bool ATelekinesis::GetGrabbableInReach(FHitResult &OutHitResult) const
{ 
    AMyriamCharacter* Player=Cast<AMyriamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0)); 

	FVector Start =Player->GetActorLocation();
	FVector End = Start  + GetActorForwardVector() * MaxGrabDistance ;	

	FCollisionShape Sphere= FCollisionShape::MakeSphere(GrabRadius);
		
    return GetWorld()->SweepSingleByChannel(
        OutHitResult,
        Start,End,
        FQuat::Identity, //No Rotation
        ECC_GameTraceChannel2,
        Sphere
        );

    
	
}

void ATelekinesis::ManageLineTraceTelekinesis()
{
    AMyriamCharacter* Player=Cast<AMyriamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));   

    //line trace
    FHitResult HitResult;
	FVector LineStartLocation=Player->GetActorLocation();
	FVector LineEndLocation= LineStartLocation + Player->GetActorForwardVector() * MaxGrabDistance;
	bool HasHit=GetWorld()->SweepSingleByChannel(HitResult,
	LineStartLocation,
	LineEndLocation,
	FQuat::Identity,
	ECC_GameTraceChannel2,
	FCollisionShape::MakeSphere(GrabRadius)
	);

    DrawDebugSphere(GetWorld(),HitResult.Location,20,12,FColor::Red,false,2);

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
		FVector TargetLocation=Player->GetActorLocation() + Player->GetActorForwardVector() *HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation,Player->GetActorRotation());
	}

}