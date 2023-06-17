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

	UFUNCTION()
	void HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetGrappleProjectileHitLocation();
	void SetGrappleProjectileHitLocation(FVector SetLocation);
	
	bool GetHasHit();
	void SetHasHit(bool SetHasHit);

	bool GetIsProjectileComingBack();
	void SetIsProjectileComingBack(bool SetIsComingBack);

	class UProjectileMovementComponent* GetProjectileMovementComponent();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Components",meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GrappleProjectileMesh;

	UPROPERTY(VisibleAnywhere,Category = "Movement")
	 UProjectileMovementComponent* ProjectileMovementComponent;

	FVector ProjectileHitLocation;

	bool HasHit=false;

	bool IsProjectileComingBack=false;

};
