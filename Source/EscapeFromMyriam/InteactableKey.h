// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "InteactableKey.generated.h"

UCLASS()
class ESCAPEFROMMYRIAM_API AInteactableKey : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteactableKey();

	virtual void BeginOverlapInteraction(AActor* OtherActor) override;

	virtual void EndOverlapInteraction(AActor* OtherActor) override;

	virtual void Interact(AActor* OtherActor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
