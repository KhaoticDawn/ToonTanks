// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	TankCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Tank Camera"));
	TankCamera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Get PlayerController
	auto playerController = Cast<APlayerController>(GetController());

	//Get Enhanced Input Subsystem & Add Input Mapping
	auto eiSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	eiSubsystem->AddMappingContext(inputMapping, 0);

	//Get Enhanced Input Component & Bind Actions
	auto playerEIcomponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	playerEIcomponent->BindAction(inputMoveForward, ETriggerEvent::Triggered, this, &ATank::Move);
	playerEIcomponent->BindAction(inputTurn, ETriggerEvent::Triggered, this, &ATank::Turn);
	playerEIcomponent->BindAction(inputFire, ETriggerEvent::Completed, this, &ATank::Fire);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Rotate Turret based on mouse location
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		RotateTurret(HitResult.ImpactPoint);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bTankAlive = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	//Store Player Controller Ref
	TankPlayerController = Cast<APlayerController>(GetController());
}

//Move the Tank forward and backward
void ATank::Move(const FInputActionValue& Value)
{
	FVector DeltaLocation(0.f);
	DeltaLocation.X = Value[0] * UGameplayStatics::GetWorldDeltaSeconds(this) * MoveSpeed;
	AddActorLocalOffset(DeltaLocation, true);
}

//Move the tank side to side
void ATank::Turn(const FInputActionValue& Value)
{
	FRotator DeltaRotation(0,0,0);
	DeltaRotation.Yaw = Value[0] * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnSpeed;
	AddActorLocalRotation(DeltaRotation, true);
}
