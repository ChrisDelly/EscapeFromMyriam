// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBBdLastKnownLocation.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h "
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_ClearBBdLastKnownLocation::UBTTask_ClearBBdLastKnownLocation()
{
    NodeName=TEXT("Clear BB Value LastKnownLocation");
}

EBTNodeResult::Type UBTTask_ClearBBdLastKnownLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp,NodeMemory);

    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    UE_LOG(LogTemp,Warning,TEXT("Cancella ultima posizione"));

    return EBTNodeResult::Succeeded;

}
