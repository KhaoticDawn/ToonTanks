// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:

	ATank();

	//Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//Components
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		class USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		class UCameraComponent* TankCamera;

	//InputMapping
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* inputMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
		class UInputAction* inputMoveForward;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
		class UInputAction* inputTurn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
		class UInputAction* inputRotateTurret;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
		class UInputAction* inputFire;

	//Movement Variables
	UPROPERTY(EditAnywhere, Category = "Movement")
		float MoveSpeed = 500;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float TurnSpeed = 200;

	//PlayerController Variable

	APlayerController* TankPlayerController;

	//Movement Functions
	void Move(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
};