// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float relativeSpeed) {
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
	float elevationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float newElevation = FMath::Clamp<float>(RelativeRotation.Pitch + elevationChange, minElevationDegrees, maxElevationDegrees);

	SetRelativeRotation(FRotator(newElevation, 0, 0));
}
