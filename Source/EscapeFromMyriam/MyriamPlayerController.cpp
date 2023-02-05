// Fill out your copyright notice in the Description page of Project Settings.


#include "MyriamPlayerController.h"
#include "Blueprint/UserWidget.h"

AMyriamPlayerController::AMyriamPlayerController()
{
    
}

void AMyriamPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if(IsValid(HudClass))
    {
        HUD=CreateWidget(this,HudClass);
        if(HUD !=nullptr)
        {
            HUD->AddToViewport();
        }
    }
    
}

