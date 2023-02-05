// Fill out your copyright notice in the Description page of Project Settings.


#include "MyriamAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


AMyriamAIController::AMyriamAIController()
{
    
}

void AMyriamAIController::BeginPlay()
{
    Super::BeginPlay();

    if(AIBehaviorTree != nullptr)
    {
        RunBehaviorTree(AIBehaviorTree);

        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

        GetBlackboardComponent()->SetValueAsVector(TEXT("Start Location"),GetPawn()->GetActorLocation());
    }
}

