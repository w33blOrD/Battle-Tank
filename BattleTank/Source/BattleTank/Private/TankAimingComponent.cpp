// Fill out your copyright notice in the Description page of Project Settings.
#include "Math/Vector.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::TargetAt(FVector HitLocation, float ProjectileLaunchSpeed)
{
	if (!Barrel) {
		UE_LOG(LogTemp, Error, TEXT("%s CAN'T FIND BARREL"), *GetOwner()->GetName());
		return;
	}

	FVector OutLaunchVelocity;
	auto ProjectileStartPoint = Barrel->GetSocketLocation(FName("LaunchPoint"));
	///UE_LOG(LogTemp,Warning,TEXT("%s, Hit Point: %s, Start Point: %s"), *GetOwner()->GetName(), *HitLocation.ToString(), *ProjectileStartPoint.ToString())
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		ProjectileStartPoint,
		HitLocation,
		ProjectileLaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	)) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); /// Returning wrong value for some reason, use Manual_Direction
		float aim_x = OutLaunchVelocity.X;
		float aim_y = OutLaunchVelocity.Y;
		float aim_z = OutLaunchVelocity.Z;
		float length = sqrt(aim_x * aim_x + aim_y * aim_y + aim_z * aim_z);
		FVector Manual_Direction = FVector(aim_x / length, aim_y / length, aim_z / length);
		///UE_LOG(LogTemp, Warning, TEXT("%s Aiming Towards %s"), *(GetOwner()->GetName()), *(Manual_Direction.ToString()))

		MoveBarrelTowards(Manual_Direction);
	}
	
}

void UTankAimingComponent::SetBarrel(UTankBarrel* Barrel)
{
	this->Barrel = Barrel;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	//Get Current and Next Rotation of Barrel
	auto CurrentRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - CurrentRotation;
	///UE_LOG(LogTemp,Warning,TEXT("Tank: %s, Delta: %s"),*(GetOwner()->GetName()), *(DeltaRotation.ToString()))
	Barrel->ElevateBarrel(5.f);
}

