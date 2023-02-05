// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyriamAIController.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFROMMYRIAM_API AMyriamAIController : public AAIController
{
	GENERATED_BODY()
	
	public:

	AMyriamAIController();

	protected:
	virtual void BeginPlay();

	private:

	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehaviorTree;
};
