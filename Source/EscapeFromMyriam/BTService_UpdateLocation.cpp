// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateLocation.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h "
#include "BehaviorTree/BlackboardComponent.h"


UBTService_UpdateLocation::UBTService_UpdateLocation()
{
    NodeName=TEXT("Update Player Location");
}

void UBTService_UpdateLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    if(PlayerPawn==nullptr)
    {
       return;
    }
    
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation"),PlayerPawn->GetActorLocation());
}
