// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto newLocation = GetActorLocation() + (PlatformVelocity * DeltaTime);
	SetActorLocation(newLocation);

	// Clamp movement to stay within bounds specified by MaxMoveDistance
	auto distanceTravelled = FVector::Dist(newLocation, StartLocation);
	if (distanceTravelled >= MaxMoveDistance)
	{
	    // If the platform has shot past where we wanted it to move, reset its location
		StartLocation = StartLocation + PlatformVelocity.GetSafeNormal() * MaxMoveDistance;
		SetActorLocation(StartLocation);

		// Reverse direction
		PlatformVelocity = -PlatformVelocity;
	}
}

