// Fill out your copyright notice in the Description page of Project Settings.


#include "GrappleProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AGrappleProjectile::AGrappleProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GrappleProjectileMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GrappleProjectile Mesh"));
	RootComponent=GrappleProjectileMesh;


	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("GrappleProjectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed=2000.f;
	ProjectileMovementComponent->MaxSpeed=2000.f;

	ProjectileMovementComponent->bSimulationEnabled=false;


}

// Called when the game starts or when spawned
void AGrappleProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	GrappleProjectileMesh->OnComponentHit.AddDynamic(this, &AGrappleProjectile::HitMesh);
	
}

void AGrappleProjectile::HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ProjectileHitLocation = Hit.Location;
	SetHasHit(true);
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

UProjectileMovementComponent* AGrappleProjectile::GetProjectileMovementComponent()
{
	return ProjectileMovementComponent;
}

