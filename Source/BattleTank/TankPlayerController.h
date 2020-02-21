// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditAnywhere)
	float CrosshairLocationX = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairLocationY = 0.28f;	
	
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& OutParam) const;
	ATank* GetControlledTank() const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
