// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolsList.h"
#include "Tool.h"
#include "MyriamCharacter.h"
#include "Grapple.h"
#include "Telekinesis.h"

// Sets default values for this component's properties
UToolsList::UToolsList()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UToolsList::BeginPlay()
{
	Super::BeginPlay();

	if(ToolsListClass.IsEmpty())
	{
		return;
	}

	UWorld* World=GetWorld();

	if(World == nullptr)
	{
		return;	
	}

	Grapple=World->SpawnActor<ATelekinesis>(ToolsListClass[ToolsListIndex]);

	AMyriamCharacter* OwnerActor=Cast<AMyriamCharacter>(GetOwner());
	Grapple->AttachToComponent(OwnerActor->GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("ToolSocket"));
	Grapple->SetOwner(this->GetOwner());

}

void UToolsList::UseTool()
{
	//for now use only grapple, in tue future there will be the activation of a tool "currently used"
	if(Grapple == nullptr)
	{
		return;
	}
	Grapple->ToolActivate();
}



// Called every frame
void UToolsList::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

