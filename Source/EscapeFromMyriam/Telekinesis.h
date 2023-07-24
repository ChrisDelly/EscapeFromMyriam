// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tool.h"
#include "Telekinesis.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFROMMYRIAM_API ATelekinesis : public ATool
{
	GENERATED_BODY()

	ATelekinesis();

	public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ToolActivate() override;	

	private:

	bool IsGrabActive = false;

	UPROPERTY(VisibleAnywhere)
	UPrimitiveComponent* ObjectToGrab;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TelekinesisMesh;

	class UPhysicsHandleComponent* GetPhysicsHandle() const;

	bool GetGrabbableInReach(FHitResult &OutHitResult) const;

	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 500;

	UPROPERTY(EditAnywhere)
	float GrabRadius = 80;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 400;

	UPROPERTY(VisibleAnywhere)
	AActor* HitActor;

	UPROPERTY(VisibleAnywhere)
	UPrimitiveComponent* HitComponent;

	void ManageLineTraceTelekinesis();
};
