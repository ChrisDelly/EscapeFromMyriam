// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetIsInOrder.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_SetIsInOrder::UBTTask_SetIsInOrder()
{
    NodeName=TEXT("Set Is In Order");
}

EBTNodeResult::Type UBTTask_SetIsInOrder::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    //OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(),false);

    return EBTNodeResult::Succeeded;
}
