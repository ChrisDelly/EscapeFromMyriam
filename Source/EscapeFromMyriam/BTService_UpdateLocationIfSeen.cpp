// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateLocationIfSeen.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "MyriamCharacter.h"

UBTService_UpdateLocationIfSeen::UBTService_UpdateLocationIfSeen()
{
    NodeName=TEXT("Update Player Location if Seen");
}


void UBTService_UpdateLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* PlayerPawn=UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    if(PlayerPawn == nullptr)
    {
        return;
    }

    if(OwnerComp.GetAIOwner() == nullptr)
    {
        return;
    };
    if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(),PlayerPawn);
        UE_LOG(LogTemp,Warning,TEXT("Visto"));
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }


}
