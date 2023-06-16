// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tool.h"
#include "HeightBox.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFROMMYRIAM_API AHeightBox : public ATool
{
	GENERATED_BODY()
	
	public:

	virtual void ToolActivate() override;


	private:
	  /*TO DO develop logic for heightbox, the following code is to be reused and rearranged for this task
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> ObjectsToDropClass;

	int32 ObjectToDropIndex=0;
	*/
};
