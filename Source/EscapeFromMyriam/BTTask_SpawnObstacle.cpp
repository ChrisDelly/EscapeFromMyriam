// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SpawnObstacle.h"
#include "Kismet/GameplayStatics.h"
#include "MyriamCharacter.h"
#include "AIController.h"


UBTTask_SpawnObstacle::UBTTask_SpawnObstacle()
{
    NodeName=TEXT("SpawnObstacle");
}

EBTNodeResult::Type UBTTask_SpawnObstacle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp,NodeMemory);

    if(OwnerComp.GetAIOwner()==nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AMyriamCharacter* AIPawn= Cast<AMyriamCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if(AIPawn==nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AIPawn->DropSomething();

    return EBTNodeResult::Succeeded;
}
