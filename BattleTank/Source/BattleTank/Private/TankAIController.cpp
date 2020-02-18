// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay(){
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController Possessing: %s"), *(ControlledTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("TankAIController: ATank object not found!"));
	}
	auto PlayerTank = GetPlayerTank();
	if(PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("%s Found %s"), *(ControlledTank->GetName()), *(PlayerTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s Did Not Find Player Tank!"), *(ControlledTank->GetName()));
	}
}

ATank* ATankAIController::GetPlayerTank() const{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
