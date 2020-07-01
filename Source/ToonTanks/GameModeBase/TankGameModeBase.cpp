// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#inlcude "ToonTanks/Pawns/PawnTank"
#inlcude "ToonTanks/Pawns/PawnTurret"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay()
{

    TargetActors = GetTargetTurretCount();

    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

    HandleGameStart();

    Super::BeginPlay();
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
    TSubclassOf<APawnTurret> ClassToFind;
    ClassToFind = APawnTurret::StaticClass();
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TurretActors);
    return TurretActors.Num();
}

void ATankGameModeBase::ActorDied(AActor *DeadActor)
{
    if(DeadActor == PlayerTank)
    {
        PlayerTank->PawnDestroyed();
        HandleGameOver(false);
    }
    else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        DestroyedTurre->PawnDestroyed();

        TargetTurrets--;

        if(TargetTurrets == 0)
        {
            HandleGameOver(true);
        }
    }
}


void ATankGameModeBase::HandleGameStart()
{
    GameStart();
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
    GameOver();
}
