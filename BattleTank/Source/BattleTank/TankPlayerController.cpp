// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* tank = GetControlledTank();
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) {
		return;
	}

	FVector hitLocation;

	// Get world location using line trace through crosshair
	if (GetSightRayHitLocation(hitLocation)) {
		// If it hits the landscape, tell controlled tank to aim at this point
		GetControlledTank()->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
	// Find crosshair position
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	FVector2D screenLocation = FVector2D(viewportSizeX * crossHairLocationX, viewportSizeY * crossHairLocationY);
	FVector lookDirection;

	// "De-project" the crosshair position to a world space direction
	if (GetLookDirection(screenLocation, lookDirection)) {
		// Line-trace along this look direction and see what we hit
		return GetLookVectorHitLocation(lookDirection, hitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const
{
	FVector cameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const
{
	FVector startLocation = PlayerCameraManager->GetCameraLocation();
	FVector endLocation = startLocation + lineTraceRange * lookDirection;
	FHitResult hitResult;
	if (GetWorld()->LineTraceSingleByChannel(
			hitResult, 
			startLocation, 
			endLocation, 
			ECC_Visibility)) {
		hitLocation = hitResult.Location;

		return true;
	}

	hitLocation = FVector(0.0);

	return false;
}
