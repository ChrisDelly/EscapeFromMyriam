// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "GameFramework/Actor.h"
#include "HidingPlace.generated.h"

UCLASS()
class ESCAPEFROMMYRIAM_API AHidingPlace : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHidingPlace();

	virtual void BeginOverlapInteraction(AActor* OtherActor) override;
	virtual void EndOverlapInteraction(AActor* OtherActor) override;
	virtual void Interact(AActor* OtherActor) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere,  meta=(AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components",meta = (AllowPrivateAccess = "true"))
	USceneComponent* InsideHidingLocation;

	//position of the character before hiding
	UPROPERTY(VisibleAnywhere)
	FVector OutsideLocation;

	//rotation of the character before hiding
	UPROPERTY(VisibleAnywhere)
	FRotator OutsideRotation;

	UPROPERTY(VisibleAnywhere,  meta=(AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere,  meta=(AllowPrivateAccess = "true"))
	class UStaticMeshComponent* VisibilityMesh;

	bool bIsHidden=false;

};
