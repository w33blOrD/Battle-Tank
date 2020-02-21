// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float MaxDegreesPerSecond = 10.f;

	UPROPERTY(EditAnywhere)
		float MaximumElevation = 30.f;

	UPROPERTY(EditAnywhere)
		float MinimumElevation = 0.f;

public:
	void ElevateBarrel(float RelativeSpeed);

};