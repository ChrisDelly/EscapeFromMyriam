// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearObjectToTideLocation.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h "
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearObjectToTideLocation::UBTTask_ClearObjectToTideLocation()
{
    NodeName=TEXT("Clear Object To Tide Location");
}

EBTNodeResult::Type UBTTask_ClearObjectToTideLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp,NodeMemory);

    if(OwnerComp.GetBlackboardComponent() != nullptr)
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
        UE_LOG(LogTemp,Warning,TEXT("Cancella posizione object to tide"));
    }
    

    return EBTNodeResult::Succeeded;

}
