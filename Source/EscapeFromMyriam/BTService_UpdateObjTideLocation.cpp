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

   TriggerSphere->OnComponentBeginOverlap.AddDynamic(this,&UBTService_UpdateObjTideLocation::OnOverlapBegin);

   OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(),ObjectToTide);

}

void UBTService_UpdateObjTideLocation::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp,Warning,TEXT("OnOverlap Begin"));
    if(OtherActor !=nullptr && OtherActor->IsA(AObjectToTide::StaticClass()))
    {
        UE_LOG(LogTemp,Warning,TEXT("Set Object Location"));
        ObjectToTide=Cast<AObjectToTide>(OtherActor);
    }
}