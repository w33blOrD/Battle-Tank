// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector TargetLocation);

	UPROPERTY(EditAnywhere, Category = Firing)
	float ProjectileLaunchSpeed = 4000.f;

protected:
	UTankAimingComponent* AimingComponent = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrel(UTankBarrel* Barrel);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurret(UTankTurret* Turret);

	UFUNCTION(BlueprintCallable, Category = Action)
	void FireProjectile();

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> Projectile;

	//Local Reference used for spawning projectiles
	UTankBarrel* Barrel;
};
