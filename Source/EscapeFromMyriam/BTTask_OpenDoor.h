// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_OpenDoor.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFROMMYRIAM_API UBTTask_OpenDoor : public UBTTaskNode
{
	GENERATED_BODY()
	
	public:

	UBTTask_OpenDoor();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	private:

	UPROPERTY(VisibleAnywhere)
	class ADoor* DoorToOpen;

	UPROPERTY(EditAnywhere)
	float MinimumActorDistance=50;
};
