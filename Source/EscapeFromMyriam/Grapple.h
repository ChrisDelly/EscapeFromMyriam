// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tool.h"
#include "Grapple.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFROMMYRIAM_API AGrapple : public ATool
{
	GENERATED_BODY()


	AGrapple();

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual void ToolActivate() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AGrappleProjectile> GrappleProjectileClass;

	AGrappleProjectile* GrappleProjectile;	


	private:
	
	bool IsCharacterBeingPulledToGrapple=false;

	UPROPERTY(EditAnywhere)
	float CharacterPullSpeed=500.f;
};
