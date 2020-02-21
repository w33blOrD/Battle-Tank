// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; 
	/*
		1 sec elevates RelativeSpeed * MaxDegreesPerSecond
		Delta Second is time needed for frame change
	*/
	auto RawElevationChange = RelativeRotation.Pitch + ElevationChange;
	auto RelativeElevation = FMath::Clamp<float>(RawElevationChange, MinimumElevation, MaximumElevation);
	SetRelativeRotation(FRotator(RelativeElevation, 0.f, 0.f));
}
