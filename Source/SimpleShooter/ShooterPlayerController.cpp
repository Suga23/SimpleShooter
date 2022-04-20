// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay(); // Иначе многое не будет работать при запуске.

    HUD = CreateWidget(this, HUDClass);
        if (HUD != nullptr)
        {
            HUD->AddToViewport();
        }
}

void AShooterPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus, bIsWinner); // Переписание метода.
    
    HUD->RemoveFromViewport();

    // Условия победы и поражения.
    if(bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass); // this - это контролле игрока(PlayerController), наша переменна подкласса.
        if (WinScreen != nullptr)
        {
            WinScreen->AddToViewport(); // При победи добавляется WinScreen widget.
        }
    }
    else
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass); // this - это контролле игрока(PlayerController), наша переменна подкласса.
        if (LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport(); // При проигрыше добавляется LoseScreen widget.
        }
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay); // Перезапускает игру вне зависимости, какое из условий if выполняется.
}
