// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolsList.h"
#include "Tool.h"
#include "MyriamCharacter.h"
#include "Grapple.h"
#include "Tool.h"
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

	Grapple=World->SpawnActor<AGrapple>(ToolsListClass[0]);
	CurrentTool=Grapple;
	Telekinesis=World->SpawnActor<ATelekinesis>(ToolsListClass[1]);

	AMyriamCharacter* OwnerActor=Cast<AMyriamCharacter>(GetOwner());
	Grapple->AttachToComponent(OwnerActor->GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("ToolSocket"));
	Grapple->SetOwner(this->GetOwner());
	Telekinesis->AttachToComponent(OwnerActor->GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("ToolSocket"));
	Telekinesis->SetOwner(this->GetOwner());
	Telekinesis->SetActorHiddenInGame(true);
}

void UToolsList::UseTool()
{
	//UE_LOG(LogTemp,Warning,TEXT("current tool %s"),*Grapple->GetName());

	if(CurrentTool == nullptr)
		return;
	if(Grapple == nullptr && Telekinesis == nullptr)
		return;

	SelectTool(ToolsListIndex);

	UE_LOG(LogTemp,Warning,TEXT("current tool %s"),*CurrentTool->GetName());
	CurrentTool->ToolActivate();
}


void UToolsList::NextTool()
{		
	if(ToolsListIndex+1==ToolsListClass.Max() && ToolsListIndex>=0)
	{	
		SelectTool(ToolsListIndex);	
		CurrentTool->SetActorHiddenInGame(true);

		//show next tool starting from the first element of the list		
		ToolsListIndex=0;		
		SelectTool(ToolsListIndex);	
		CurrentTool->SetActorHiddenInGame(false);
	}
	else if (ToolsListIndex>=0)
	{
		//hide current tool
		SelectTool(ToolsListIndex);	
		CurrentTool->SetActorHiddenInGame(true);

		//show next tool 
		ToolsListIndex++;		
		SelectTool(ToolsListIndex);			
		CurrentTool->SetActorHiddenInGame(false);
	}
}

void UToolsList::PreviousTool()
{
	if(ToolsListIndex-1<0)
		{	
			SelectTool(ToolsListIndex);	
			CurrentTool->SetActorHiddenInGame(true);

			//show next tool starting from the first element of the list		
			ToolsListIndex=ToolsListClass.Max()-1;		
			SelectTool(ToolsListIndex);			
			CurrentTool->SetActorHiddenInGame(false);
		}
		else
		{
			SelectTool(ToolsListIndex);					
			//hide current tool			
			CurrentTool->SetActorHiddenInGame(true);

			//show next tool starting from the first element of the list
			ToolsListIndex--;		
			SelectTool(ToolsListIndex);					
			CurrentTool->SetActorHiddenInGame(false);
		}
}

// Called every frame
void UToolsList::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UToolsList::SelectTool(int32 Index)
{
	switch (Index)
		{
		case 0:
			CurrentTool=Grapple;
			break;
		case 1:
			CurrentTool=Telekinesis;
			break;
		
		default:
			break;
		}
}