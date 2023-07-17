// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//Make Turret face player
	if (TankInRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}

}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	//Set Tank ref
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	//Set timer for turret fire rate
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

//If Tank is in range, then fire
void ATower::CheckFireCondition()
{
	if (Tank == nullptr)
	{
		return;
	}

	if (TankInRange() && Tank->bTankAlive)
	{
			Fire();
	}
}

//Check if Tank is in range
bool ATower::TankInRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		if (Distance <= FireRange)
		{
			return true;
		}
	}

		return false;
}