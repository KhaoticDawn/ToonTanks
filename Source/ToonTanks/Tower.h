// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Store the Tank ref
	class ATank* Tank;

	//Exposed combat variables
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 750;

	//Unexposed combat variables
	FTimerHandle FireRateTimerHandle;
	float FireRate = 2;

	//Combat functions
	void CheckFireCondition();
	bool TankInRange();
};
