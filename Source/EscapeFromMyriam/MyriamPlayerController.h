// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyriamPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFROMMYRIAM_API AMyriamPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AMyriamPlayerController();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget>HudClass;

	UPROPERTY(EditAnywhere)
	UUserWidget* HUD;
	
	
};
