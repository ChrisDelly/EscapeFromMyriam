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
	virtual void ToolActivate() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AGrappleProjectile> GrappleProjectileClass;

	AGrappleProjectile* GrappleProjectile;	
};
