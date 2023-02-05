// Fill out your copyright notice in the Description page of Project Settings.


#include "MyriamCharacter.h"
#include "Camera/CameraComponent.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AMyriamCharacter::AMyriamCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm= CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	ObjectSpawnPoint=CreateDefaultSubobject<USceneComponent>(TEXT("Object Spawn Point"));
	ObjectSpawnPoint->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AMyriamCharacter::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();

    if(World!=nullptr)
    {
        UGameplayStatics::GetAllActorsOfClass(World, ATargetPoint::StaticClass(), TargetPointsList);
    }

    
	
}

// Called every frame
void AMyriamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	

}

// Called to bind functionality to input
void AMyriamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move Forward"),this,&AMyriamCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Move Right"), this, &AMyriamCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("Look Up"),this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("Turn Right"),this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump",EInputEvent::IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction("DropSomething",EInputEvent::IE_Pressed,this,&AMyriamCharacter::DropSomething);

}

void AMyriamCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AMyriamCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AMyriamCharacter::DropSomething()
{
	if(ObjectToDropClass == nullptr)
	{
		return;
	}
	
	UWorld* World=GetWorld();
	if(World == nullptr)
	{
		return;
	}

	FTransform SpawnTransform = GetActorTransform();
	if(ObjectToDropClass==nullptr)
	{
		return;
	}
	
	auto SpawnedObject = World->SpawnActor<AActor>(ObjectToDropClass,ObjectSpawnPoint->GetComponentLocation(),ObjectSpawnPoint->GetComponentRotation());	


}

TArray<AActor*> AMyriamCharacter::GetTargetPointList()
{
	return TargetPointsList;
}