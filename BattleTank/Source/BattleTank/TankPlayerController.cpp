// Fill out your copyright notice in the Description page of Project Settings.
#include"Tank.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	///UE_LOG(LogTemp, Warning, TEXT("Link Start"));
	auto ControlledTank = GetControlledTank();
	if (ControlledTank) {
		///UE_LOG(LogTemp, Warning, TEXT("Controlling: %s"), *(ControlledTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("ATank Pawn not found!"));
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) {
		UE_LOG(LogTemp, Error, TEXT("AimTowarsCrosshair Failed, ATank Pawn not found!"));
		return;
	}

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		///UE_LOG(LogTemp, Warning, TEXT("Target Location: %s"), *HitLocation.ToString())
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairLocationX, ViewportSizeY * CrosshairLocationY);
	///UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *ScreenLocation.ToString());
	FVector LookDirection;
	if(GetLookDirection(ScreenLocation, LookDirection)){
		///UE_LOG(LogTemp,Warning, TEXT("Target Direction: %s"), *LookDirection.ToString())
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		WorldLocation, 
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const{
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		PlayerCameraManager->GetCameraLocation(),
		PlayerCameraManager->GetCameraLocation() + (LookDirection * LineTraceRange),
		ECollisionChannel::ECC_Visibility
	)){
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.f);
	return false;
}

