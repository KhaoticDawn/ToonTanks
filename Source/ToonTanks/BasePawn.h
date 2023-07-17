// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraShakeBase.h"
#include "LegacyCameraShake.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

private:
	//Component variables
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		class UCapsuleComponent* CapsuleComp;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		class USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		UParticleSystem* DeathEffect;

	UPROPERTY(EditAnywhere, Category = "Combat")
		class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
		class TSubclassOf<UCameraShakeBase> DeathShakeClass;

protected:
	//Combat functions
	void RotateTurret(FVector LookAtTarget);
	void Fire();

};
