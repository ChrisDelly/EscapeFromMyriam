// Fill out your copyright notice in the Description page of Project Settings.


#include "Telekinesis.h"
#include "Kismet/GameplayStatics.h"
#include "MyriamCharacter.h"


ATelekinesis::ATelekinesis()
{
    
}

void ATelekinesis::Tick(float DeltaTime)
{
    
}

void ATelekinesis::ToolActivate()
{
    AMyriamCharacter* Player=Cast<AMyriamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

    if(Player == nullptr)
        return;
    
    ObjectToGrab=Player->GetHitComponent();
    //If grab is active release the object/actor currently grabbed
    if(IsGrabActive)
    {
        IsGrabActive = false;
        ObjectToGrab=nullptr;
        UE_LOG(LogTemp,Warning,TEXT("Release"));
    }
    else
    {
         //if the object/actor can be grabbed, grab it
       
        if (ObjectToGrab == nullptr)
        {
            UE_LOG(LogTemp,Warning,TEXT("Can't grab"));    
            return;
        }

        if (ObjectToGrab->ComponentHasTag(TEXT("Grabbable")))
        {                   
            IsGrabActive = true;
            UE_LOG(LogTemp,Warning,TEXT("componente %s"),*ObjectToGrab->GetName() );   
            UE_LOG(LogTemp,Warning,TEXT("Grab"));
        }
        
    }
}


