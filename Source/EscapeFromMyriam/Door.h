// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class ESCAPEFROMMYRIAM_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere,  meta=(AllowPrivateAccess = "true"))
	class UBoxComponent* DoorTriggerBox;

	UPROPERTY(VisibleAnywhere,  meta=(AllowPrivateAccess = "true"))
	class UStaticMeshComponent* LeftDoor;

	UPROPERTY(VisibleAnywhere,  meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightDoor;

	void OpenDoor();

	void CloseDoor();

	UPROPERTY(EditAnywhere)
	float RotationAmount=90.f;

	UPROPERTY(EditAnywhere)
	float RotationSpeed=5.f;

};
