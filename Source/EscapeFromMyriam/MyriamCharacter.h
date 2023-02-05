// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyriamCharacter.generated.h"

UCLASS()
class ESCAPEFROMMYRIAM_API AMyriamCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyriamCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category= Camera )
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void DropSomething();

	TArray<AActor*> GetTargetPointList();

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


UPROPERTY(EditDefaultsOnly)
TSubclassOf<AActor> ObjectToDropClass;



};
