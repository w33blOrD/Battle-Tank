// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::RotateTurret(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	float YawChange = RelativeSpeed * MaxRotationPerSecond * GetWorld()->DeltaTimeSeconds;
	float RelativeYawRotation = RelativeRotation.Yaw + YawChange;
	///UE_LOG(LogTemp, Warning, TEXT("%f"), YawChange);
	SetRelativeRotation(FRotator(0.f, RelativeYawRotation,0.f));
}