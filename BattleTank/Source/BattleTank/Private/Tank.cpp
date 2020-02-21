// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Creating an Aiming Component for the tank
	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::AimAt(FVector TargetLocation)
{
	///UE_LOG(LogTemp, Warning, TEXT("%s"), *TargetLocation.ToString())
	AimingComponent->TargetAt(TargetLocation,ProjectileLaunchSpeed);
}

void ATank::SetBarrel(UTankBarrel* Barrel)
{
	AimingComponent->SetBarrel(Barrel);
}

void ATank::SetTurret(UTankTurret* Turret)
{
	AimingComponent->SetTurret(Turret);
}

void ATank::FireProjectile()
{
	UE_LOG(LogTemp, Warning, TEXT("Firing Projectile!"))
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

