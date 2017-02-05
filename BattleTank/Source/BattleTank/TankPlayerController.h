// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere)
	float crossHairLocationX = 0.5;
	UPROPERTY(EditAnywhere)
	float crossHairLocationY = 0.33333;
	UPROPERTY(EditAnywhere)
	float lineTraceRange = 1000000;

	ATank* GetControlledTank() const;

	// Start moving the tank barrel to where the crosshair intersects the world geometry
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& hitLocation) const;
	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;
	bool GetLookVectorHitLocation(FVector lookDirection, FVector &hitLocation) const;
};
