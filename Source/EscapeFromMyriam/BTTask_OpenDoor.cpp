// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_OpenDoor.h"
#include "MyriamAIController.h"
#include "MyriamCharacter.h"
#include "Math/Vector.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Door.h"

UBTTask_OpenDoor::UBTTask_OpenDoor()
{
    NodeName=TEXT("Open Door");
}


EBTNodeResult::Type UBTTask_OpenDoor::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp,NodeMemory);

    if(OwnerComp.GetBlackboardComponent()==nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AMyriamCharacter* AIPawn=Cast<AMyriamCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    USphereComponent* TriggerSphere=AIPawn->GetSphereTrigger();

    if(AIPawn == nullptr)
    {
         return EBTNodeResult::Failed;
    }

    if(TriggerSphere == nullptr)
    {
         return EBTNodeResult::Failed;
    }

    TriggerSphere->OnComponentBeginOverlap.AddUniqueDynamic(this,&UBTTask_OpenDoor::OnOverlapBegin);
    TriggerSphere->OnComponentEndOverlap.AddUniqueDynamic(this,&UBTTask_OpenDoor::OnOverlapEnd);

    if(DoorToOpen == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    UBoxComponent* DoorOpenRangeBox= DoorToOpen->GetDoorIAOpenRangeBox();
    // se l-IA é nell-area della porta da aprire
    if(DoorOpenRangeBox==nullptr)
    {
        return EBTNodeResult::Failed;
    }

    if(AIPawn->IsOverlappingActor(DoorToOpen))
    {
        UE_LOG(LogTemp,Warning,TEXT("IA is overlapping door area"));
        
        //se l'IA é vicinissima al punto da controllare (potrebbe essere non possibile trovarsi nel punto esatto)      
        if(DoorToOpen->GetIsOpenDoor())
        {
            UE_LOG(LogTemp,Warning,TEXT("AI apre la porta"));
            //Apri la porta
            DoorToOpen->OpenDoor();
            DoorToOpen->SetIsOpenDoor(true);            
        }        
    }
    

    
    return EBTNodeResult::Succeeded;


}



void UBTTask_OpenDoor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
   
    if(OtherActor !=nullptr && OtherActor->IsA(ADoor::StaticClass()))
    {
       UE_LOG(LogTemp,Warning,TEXT("Assegna porta %s alla variabile"),*OtherActor->GetName());
        DoorToOpen=Cast<ADoor>(OtherActor);
    }
}

void UBTTask_OpenDoor::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if(DoorToOpen != nullptr)
    {
        
        DoorToOpen=nullptr;
    }
}