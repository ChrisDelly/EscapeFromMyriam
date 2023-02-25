// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_EndTheGame.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFROMMYRIAM_API UBT_EndTheGame : public UBTTaskNode
{
	GENERATED_BODY()
	
	UBT_EndTheGame();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LosingWidgetClass;

	UPROPERTY(VisibleAnywhere)
	UUserWidget* LosingScreen;
};
