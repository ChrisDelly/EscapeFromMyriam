// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_UpdateTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFROMMYRIAM_API UBTTask_UpdateTargetPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	public:

	UBTTask_UpdateTargetPoint();
	
	protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	private:

	UPROPERTY(VisibleAnywhere)
	int32 TargetIndex=0;
};
