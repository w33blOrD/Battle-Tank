// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Link Start"));
	auto ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Controlling: %s"), *(ControlledTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("ATank Pawn not found!"));
	}
}