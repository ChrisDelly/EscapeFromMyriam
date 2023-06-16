// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Door.generated.h"

UCLASS()
class ESCAPEFROMMYRIAM_API ADoor : public AActor,public IInteractInterface
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
	
	void OpenDoor();
	void CloseDoor();
	

	void SetIsOpenDoor(bool IsOpen);
	bool GetIsOpenDoor();

	virtual void BeginOverlapInteraction(AActor* OtherActor) override;

	virtual void EndOverlapInteraction(AActor* OtherActor) override;

	virtual void Interact(AActor* OtherActor) override;

	

private:

	UPROPERTY(VisibleAnywhere,  meta=(AllowPrivateAccess = "true"))
	class UBoxComponent* DoorTriggerBox;

	UPROPERTY(VisibleAnywhere,  meta=(AllowPrivateAccess = "true"))
	class UBoxComponent* DoorIAOpenRangeBox;

	UPROPERTY(VisibleAnywhere,  meta=(AllowPrivateAccess = "true"))
	class UStaticMeshComponent* LeftDoor;





	UPROPERTY(EditAnywhere)
	float RotationAmount=90.f;

	UPROPERTY(EditAnywhere)
	float RotationSpeed=5.f;

	UPROPERTY(VisibleAnywhere)
	bool bIsOpen=false;

	void OpenOrCloseDoor();

	public:

	UBoxComponent* GetDoorIAOpenRangeBox();
};
