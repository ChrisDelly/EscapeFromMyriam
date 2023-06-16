// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateLocationIfSeen.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFROMMYRIAM_API UBTService_UpdateLocationIfSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	public:

	UBTService_UpdateLocationIfSeen();

	protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	float IncreasedMaxSpeed=600;

	UPROPERTY(EditAnywhere)
	float NormalMaxSpeed=450;

	
};
