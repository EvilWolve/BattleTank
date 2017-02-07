// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet)
{
	barrel = barrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed) {
	if (!barrel) {
		return;
	}
	FVector outLaunchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));

	bool hasAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		outLaunchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (hasAimSolution) {
		FVector aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrel(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector aimDirection) {
	FRotator barrelRotation = barrel->GetForwardVector().Rotation();
	FRotator aimAsRotation = aimDirection.Rotation();
	FRotator deltaRotation = aimAsRotation - barrelRotation;

	barrel->Elevate(deltaRotation.Pitch);
}