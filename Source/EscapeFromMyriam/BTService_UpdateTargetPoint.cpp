// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateTargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyriamCharacter.h"


UBTService_UpdateTargetPoint::UBTService_UpdateTargetPoint()
{
    NodeName=TEXT("Update Target Point");

}

void UBTService_UpdateTargetPoint::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);
    
}
