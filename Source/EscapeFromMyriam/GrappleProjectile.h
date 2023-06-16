// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrappleProjectile.generated.h"

UCLASS()
class ESCAPEFROMMYRIAM_API AGrappleProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrappleProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Components",meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GrappleProjectileMesh;

	UPROPERTY(VisibleAnywhere,Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;


};
