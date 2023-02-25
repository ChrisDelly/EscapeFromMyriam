// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WinningTriggerVolume.generated.h"

UCLASS()
class ESCAPEFROMMYRIAM_API AWinningTriggerVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWinningTriggerVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(VisibleAnywhere,  meta=(AllowPrivateAccess = "true"))
	class UBoxComponent* WinVolume;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinningWidgetClass;

	UPROPERTY(VisibleAnywhere)
	UUserWidget* WinningScreen;

};
