// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InteractInterface.h"
#include "MyriamCharacter.generated.h"

UCLASS()
class ESCAPEFROMMYRIAM_API AMyriamCharacter : public ACharacter,public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyriamCharacter();

	class USphereComponent* GetSphereTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category= Camera )
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="Inventory")
	TArray<FString> Inventory;

	UPROPERTY(VisibleAnywhere,  meta=(AllowPrivateAccess = "true"))
	USphereComponent* SphereTrigger;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void DropSomething();

	void Action();

	TArray<AActor*> GetTargetPointList();
	
	virtual void BeginOverlapInteraction(AActor* OtherActor) override;

	virtual void EndOverlapInteraction(AActor* OtherActor) override;

	virtual void Interact(AActor* OtherActor) override;

	

private:

UPROPERTY(EditAnywhere)
float TurnRate=10;

UPROPERTY(EditAnywhere)
float SpawnOffsetLocation=50;

UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components",meta = (AllowPrivateAccess = "true"))
USceneComponent* ObjectSpawnPoint;

void MoveForward(float AxisValue);
void MoveRight(float AxisValue);


UPROPERTY(VisibleAnywhere)
TArray<AActor*> TargetPointsList;


UPROPERTY(EditAnywhere)
TArray<TSubclassOf<AActor>> ObjectsToDropClass;

int32 ObjectToDropIndex=0;

UPROPERTY(EditAnywhere)
float MaxGrabDistance =200;

UPROPERTY(EditAnywhere)
float SweepSize=70;

UPROPERTY(VisibleAnywhere)
AActor* HitActor;

void OpenOrCloseDoor(AActor* Actor);


};
