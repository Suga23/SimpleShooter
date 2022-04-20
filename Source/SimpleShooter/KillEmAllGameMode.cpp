// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled) 
{
    Super::PawnKilled(PawnKilled);
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if(PlayerController != nullptr)
    {
        EndGame(false); // Передаётся false, если котроллер не принадлежит игроку, другой вариант в уроке 217.
    }
    
    for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld())) // Получение данных о существующих контроллерах, GetWorld() указание на каком конкретно уровне следует брать данные о контроллерах.
    {
        if(!Controller->IsDead()) // Если в метод не передаются контроллер, то return.
        {
            return;
        }
    }
    EndGame(true); // Игра завершена успешно.
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    // Этот цикл проходит через каждый контроллер в уровне/игровом мире.
    // Помимо этого можно определить контроллер игрока без необходимости использовать метод Cast.
    for(AController* Controller : TActorRange<AController>(GetWorld())) // TActorRange - шаблон вещи. Данная строка возвращает объект диапазона,
    {                                                                   // похожий на список, который проходит по всем контроллерам. И это можно использовать в полном цикле.
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner; // Идёт булево вычисления, для того чтобы выяснить, является ли переданный контроллер, контроллером игрока.
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner); // Раньше тут был nullptr, теперь Controller->GetPawn() - Сообщает о том, на ком контроллер должен быть сфокусирован, на игроке или кто его убил.
    }                                                                    
}