// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_UpdateTargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyriamCharacter.h"



UBTTask_UpdateTargetPoint::UBTTask_UpdateTargetPoint()
{
    NodeName=TEXT("Update Target Point");
}

EBTNodeResult::Type UBTTask_UpdateTargetPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp,NodeMemory);

     if(OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    };

    AMyriamCharacter* AIPawn=Cast<AMyriamCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    TArray<AActor*>TargetList=AIPawn->GetTargetPointList();
    //se l-indice della lista ha valore pari alla grandezza della lista
    // impostalo al primo elemento della lista 
    if(TargetIndex == TargetList.Num() )
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(),TargetList[0]);
        TargetIndex=0;
    }

    //se l'indice del target si trova all'interno della lista incrementalo di uno
    if(TargetIndex>=0 && TargetIndex <TargetList.Num())
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(),TargetList[TargetIndex]);
        TargetIndex++;
    }
    return EBTNodeResult::Succeeded;
}
