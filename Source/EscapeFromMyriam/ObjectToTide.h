// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "ObjectToTide.generated.h"

UCLASS()
class ESCAPEFROMMYRIAM_API AObjectToTide : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectToTide();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool GetIsInOrder();

	void SetIsInOrder(bool InOrder);

	
	virtual void BeginOverlapInteraction(AActor* OtherActor) override;

	virtual void EndOverlapInteraction(AActor* OtherActor) override;

	virtual void Interact(AActor* OtherActor) override;

private:

	UPROPERTY(EditAnywhere)
	bool bIsInOrder=true;

};
