// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetIsInOrder.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ObjectToTide.h"


UBTTask_SetIsInOrder::UBTTask_SetIsInOrder()
{
    NodeName=TEXT("Set Is In Order");
}

EBTNodeResult::Type UBTTask_SetIsInOrder::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);


    AObjectToTide* ObjectToTide = Cast<AObjectToTide>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

    if(ObjectToTide == nullptr)
    {
       return EBTNodeResult::Failed;
    }

     ObjectToTide->SetIsInOrder(true);

    return EBTNodeResult::Succeeded;
}
