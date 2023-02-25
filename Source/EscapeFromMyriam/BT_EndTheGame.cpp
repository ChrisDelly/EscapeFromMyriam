// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_EndTheGame.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


UBT_EndTheGame::UBT_EndTheGame()
{
    NodeName=TEXT("EndTheGame");
}

EBTNodeResult::Type UBT_EndTheGame::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(IsValid(LosingWidgetClass))
	{
        UE_LOG(LogTemp,Warning,TEXT("Lose"));
		LosingScreen=CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(),0),LosingWidgetClass);
		if(LosingScreen!=nullptr)
		{
			LosingScreen->AddToViewport();
		}
	}

    return EBTNodeResult::Succeeded;

}

