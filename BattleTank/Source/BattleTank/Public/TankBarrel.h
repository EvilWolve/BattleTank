// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent), hideCategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxDegreesPerSecond = 20;
	UPROPERTY(EditAnywhere, Category = Setup)
	float minElevationDegrees = 0;
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxElevationDegrees = 40;
	
public:
	// -1 is max down speed, +1 max up speed
	void Elevate(float relativeSpeed);
};
