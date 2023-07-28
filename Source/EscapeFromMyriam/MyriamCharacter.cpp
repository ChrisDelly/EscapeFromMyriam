// Fill out your copyright notice in the Description page of Project Settings.


#include "MyriamCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Door.h"
#include "ObjectToTide.h"
#include "Math/UnrealMathUtility.h"
#include "Components/SphereComponent.h"
#include "Tool.h"
#include "Grapple.h"
#include "Heightbox.h"
#include "DrawDebugHelpers.h"
#include "ToolsList.h"
#include "GameFramework/CharacterMovementComponent.h"
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

	SphereTrigger=CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Trigger"));
	SphereTrigger->SetupAttachment(RootComponent);
	SphereTrigger->SetSphereRadius(300);

	ToolsList=CreateDefaultSubobject<UToolsList>(TEXT("Tools List"));

	CurrentStamina=MaxStamina;

}


// Called when the game starts or when spawned
void AMyriamCharacter::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();

	if(World == nullptr)
	{
		return;
	}
   
    UGameplayStatics::GetAllActorsOfClass(World, ATargetPoint::StaticClass(), TargetPointsList);
	

	
}

// Called every frame
void AMyriamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	FVector LineStartLocation=Camera->GetComponentLocation();
	FVector LineEndLocation= LineStartLocation + Camera->GetForwardVector() * MaxGrabDistance;
	bool HasHit=GetWorld()->SweepSingleByChannel(HitResult,
	LineStartLocation,
	LineEndLocation,
	FQuat::Identity,
	ECC_GameTraceChannel1,
	FCollisionShape::MakeSphere(SweepSize)
	);

	//DrawDebugLine(GetWorld(),LineStartLocation,LineEndLocation,FColor::Red,false,10,1,20);

	if(HasHit)
	{
		HitActor=HitResult.GetActor();
		//UE_LOG(LogTemp,Warning,TEXT("Hit! %s"),*HitActor->GetActorNameOrLabel());

		
	}
	else
	{
		HitActor=nullptr;
	}
	
	if(IsSprinting)
	{
		ConsumeStamina(DeltaTime);
	}
	else
	{
		RechargeStamina(DeltaTime);
	}
	
	
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
	PlayerInputComponent->BindAction("Fire",EInputEvent::IE_Pressed,this,&AMyriamCharacter::Fire);
	PlayerInputComponent->BindAction("Action",EInputEvent::IE_Pressed,this,&AMyriamCharacter::Action);

	PlayerInputComponent->BindAction("Sprint",EInputEvent::IE_Pressed,this,&AMyriamCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint",EInputEvent::IE_Released,this,&AMyriamCharacter::EndSprint);

	PlayerInputComponent->BindAction("NextTool",EInputEvent::IE_Pressed,this,&AMyriamCharacter::NextTool);
	PlayerInputComponent->BindAction("PreviousTool",EInputEvent::IE_Pressed,this,&AMyriamCharacter::PreviousTool);



}

void AMyriamCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AMyriamCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}



void AMyriamCharacter::Fire()
{


	if(ToolsList == nullptr)
	{
		return;
	}

	ToolsList->UseTool();
}

void AMyriamCharacter::Action()
{

	if(HitActor==nullptr)
		{
			return;
		}

	
	bool bHasInterface=HitActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass());

	if(!bHasInterface)
	{
		return;
	}
	
	Cast<IInteractInterface>(HitActor)->Interact(HitActor);
}

void AMyriamCharacter::BeginOverlapInteraction(AActor* OtherActor)
{
	
}

void AMyriamCharacter::EndOverlapInteraction(AActor* OtherActor)
{
	
}

void AMyriamCharacter::Interact(AActor* OtherActor)
{	
	if(HitActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
	{
		Cast<IInteractInterface>(HitActor)->Interact(this);
	}

	
}

TArray<FString> AMyriamCharacter::GetInventory() const
{
	return Inventory;
}

void AMyriamCharacter::AddItemToInventory(FString item)
{
	Inventory.Add(item);
}

USpringArmComponent* AMyriamCharacter::GetSpringArm()
{
	return SpringArm;
}

UCameraComponent* AMyriamCharacter::GetCamera()
{
	return Camera;
}

UCharacterMovementComponent* AMyriamCharacter::GetMovementComponent()
{
	return GetCharacterMovement();
}

void AMyriamCharacter::StartSprint()
{
	GetMovementComponent()->MaxWalkSpeed+=SprintSpeedAmount;
	IsSprinting=true;
}

void AMyriamCharacter::EndSprint()
{
	GetMovementComponent()->MaxWalkSpeed-=SprintSpeedAmount;
	IsSprinting=false;
}



TArray<AActor*> AMyriamCharacter::GetTargetPointList()
{
	return TargetPointsList;
}

void AMyriamCharacter::OpenOrCloseDoor(AActor* Actor)
{
	ADoor* Door=Cast<ADoor>(Actor);
	Door->OpenDoor();

				
}

void AMyriamCharacter::ConsumeStamina(float DeltaTime)
{
	
	if(CurrentStamina-StaminaConsumptionAmount*DeltaTime<=0)
	{
		CurrentStamina=0;
		IsSprinting=false;
	}
	else
	{
		CurrentStamina-=StaminaConsumptionAmount*DeltaTime;
	}
	
	
}

void AMyriamCharacter::RechargeStamina(float DeltaTime)
{
	if(CurrentStamina+StaminaConsumptionAmount*DeltaTime>=MaxStamina)
	{
		CurrentStamina=MaxStamina;		
	}
	else
	{
		CurrentStamina+=StaminaConsumptionAmount*DeltaTime;
	}
	
}

void AMyriamCharacter::NextTool()
{
	ToolsList->NextTool();
}

void AMyriamCharacter::PreviousTool()
{
ToolsList->PreviousTool();	
}


USphereComponent* AMyriamCharacter::GetSphereTrigger()
{
	return SphereTrigger;
}