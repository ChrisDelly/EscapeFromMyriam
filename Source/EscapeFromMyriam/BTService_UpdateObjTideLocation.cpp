// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateObjTideLocation.h"
#include "MyriamAIController.h"
#include "MyriamCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "ObjectToTide.h"
#include "Kismet/GameplayStatics.h"


UBTService_UpdateObjTideLocation::UBTService_UpdateObjTideLocation()
{
    NodeName=TEXT("UpdateObjectToTideLocation");
    
        
}



void UBTService_UpdateObjTideLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if(OwnerComp.GetAIOwner()==nullptr)
    {
        return;
    }

   AMyriamCharacter* AIPawn=Cast<AMyriamCharacter>(OwnerComp.GetAIOwner()->GetPawn());
   USphereComponent* TriggerSphere=AIPawn->GetSphereTrigger();

   if (AIPawn == nullptr)
   {
    return;
   }

   if(TriggerSphere == nullptr)
   {
    return;
   }

 //SE MYRIAM É NEL RAGGIO DELL-OGGETTO IMPOSTA BLACKBOARD 
   TriggerSphere->OnComponentBeginOverlap.AddUniqueDynamic(this,&UBTService_UpdateObjTideLocation::OnOverlapBegin);
   TriggerSphere->OnComponentEndOverlap.AddUniqueDynamic(this,&UBTService_UpdateObjTideLocation::OnOverlapEnd);
   if(ObjectToTide != nullptr)
   {
    //se l'oggetto é nel raggio ma non é in ordine segna posizione
    if(!(ObjectToTide->GetIsInOrder()))//se false
    {
         UE_LOG(LogTemp,Warning,TEXT("Disordine"));
         OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(),ObjectToTide);
    }else
    {
        //se true
        //é in ordine
         UE_LOG(LogTemp,Warning,TEXT("In Ordine"));
        OwnerComp.GetAIOwner()->GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }   
   }

  
   

}

void UBTService_UpdateObjTideLocation::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
   
    if(OtherActor !=nullptr && OtherActor->IsA(AObjectToTide::StaticClass()))
    {
       
        ObjectToTide=Cast<AObjectToTide>(OtherActor);
    }
}

void UBTService_UpdateObjTideLocation::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if(ObjectToTide != nullptr)
    {
        
        ObjectToTide=nullptr;
    }
}