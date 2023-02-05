// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateLocation.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFROMMYRIAM_API UBTService_UpdateLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	public:
	UBTService_UpdateLocation();

	protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
