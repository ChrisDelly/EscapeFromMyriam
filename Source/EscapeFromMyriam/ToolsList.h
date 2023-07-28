// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ToolsList.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEFROMMYRIAM_API UToolsList : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UToolsList();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UseTool();
	
	void NextTool();
	void PreviousTool();
private:

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ATool>> ToolsListClass;

	int32 ToolsListIndex=0;

	class ATool* CurrentTool;
	class AGrapple* Grapple;
	class ATelekinesis* Telekinesis;
	

	void SelectTool(int32 Index);

	
};
