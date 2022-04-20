// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot() 
{
    NodeName = "Shoot";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (OwnerComp.GetAIOwner() == nullptr) // Получение объекта-обладателя AI и проверка на null.
    {
        return EBTNodeResult::Failed;
    }

    AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn()); // Получение AIController при помощи GetPawn() и переделывание его AShooterCharacter при помощи метода Cast.
    if (Character == nullptr) // Проверка на null.
    {
        return EBTNodeResult::Failed;
    }

    Character->Shoot(); // Вызов метода Shoot().

    return EBTNodeResult::Succeeded; // Если успешно, то не надо продолжительно вызывать тик, нет необходимости выполнять эту задачу, больше чем один кадр(frame).
}