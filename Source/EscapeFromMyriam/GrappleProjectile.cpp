// Fill out your copyright notice in the Description page of Project Settings.


#include "GrappleProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "MyriamCharacter.h"
#include "CableComponent.h"
#include "Grapple.h"


// Sets default values
AGrappleProjectile::AGrappleProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GrappleProjectileMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GrappleProjectile Mesh"));
	RootComponent=GrappleProjectileMesh;

	SphereTrigger =CreateDefaultSubobject<USphereComponent>(TEXT("Sphere collision"));
	SphereTrigger->SetupAttachment(GrappleProjectileMesh);


	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("GrappleProjectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed=2000.f;
	ProjectileMovementComponent->MaxSpeed=2000.f;

	ProjectileSpeed=ProjectileMovementComponent->MaxSpeed;

	ProjectileMovementComponent->bSimulationEnabled=false;

	GrappleProjectileCable=CreateDefaultSubobject<UCableComponent>(TEXT("Grapple projectile Cable"));
	GrappleProjectileCable->SetupAttachment(GrappleProjectileMesh);
	GrappleProjectileCable->SetVisibility(false);


}

// Called when the game starts or when spawned
void AGrappleProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	GrappleProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AGrappleProjectile::OverlapBegin);
	GrappleProjectileMesh->OnComponentHit.AddDynamic(this, &AGrappleProjectile::HitMesh);
	
}

void AGrappleProjectile::HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ProjectileHitLocation = Hit.Location;
	UE_LOG(LogTemp,Warning,TEXT("Hit!"));
	SetHasHit(true);
}

void AGrappleProjectile::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(OtherActor != nullptr
	&& !(OtherActor->IsA(AMyriamCharacter::StaticClass())) 
	&& !(OtherActor->IsA(AGrapple::StaticClass())) 
	&& !(OtherActor->IsA(AGrappleProjectile::StaticClass()))
	)
	{
		ProjectileMovementComponent->MaxSpeed=0.0000000000001;
		UE_LOG(LogTemp,Warning,TEXT("Overlap! %s"),*OtherActor->GetName());
		SetHasHit(true);
	}
	
}

// Called every frame
void AGrappleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AGrappleProjectile::GetGrappleProjectileHitLocation()
{
	return ProjectileHitLocation;
}

void AGrappleProjectile::SetGrappleProjectileHitLocation(FVector SetLocation)
{
	ProjectileHitLocation=SetLocation;
}

bool AGrappleProjectile::GetHasHit()
{
	return HasHit;
}

void AGrappleProjectile::SetHasHit(bool SetHasHit)
{
	HasHit=SetHasHit;
}

bool AGrappleProjectile::GetIsProjectileComingBack()
{
	return IsProjectileComingBack;
}

void AGrappleProjectile::SetIsProjectileComingBack(bool SetIsComingBack)
{
	IsProjectileComingBack=SetIsComingBack;
}

bool AGrappleProjectile::GetIsProjectileMoving()
{
	return IsProjectileMoving;
}

void AGrappleProjectile::SetIsProjectileMoving(bool SetMoving)
{
	IsProjectileMoving=SetMoving;
}

float AGrappleProjectile::GetProjectileMaxSpeed()
{
	return ProjectileSpeed;
}

void AGrappleProjectile::SetProjectileMaxSpeed()
{
	ProjectileMovementComponent->MaxSpeed=ProjectileSpeed;
}

class UCableComponent* AGrappleProjectile::GetGrappleProjectileCable()
{
	return GrappleProjectileCable;
}

UProjectileMovementComponent* AGrappleProjectile::GetProjectileMovementComponent()
{
	return ProjectileMovementComponent;
}

