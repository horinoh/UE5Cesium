// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobeAwareDefaultPawn.h"
#include "ScesiumPawn.generated.h"

class UInputAction;
struct FInputActionInstance;

//!< AGlobeAwareDefaultPawn ‚ðŽg‚¤‚É‚Í UE5CesiumBuild.cs ‚Ö "CesiumRuntime" ‚ð’Ç‰Á‚·‚é•K—v‚ª‚ ‚é

/**
 * 
 */
UCLASS()
class UE5CESIUM_API AScesiumPawn : public AGlobeAwareDefaultPawn
{
	GENERATED_BODY()
	
	AScesiumPawn();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnFlight(const FInputActionInstance& Instance);

	UFUNCTION()
	void OnFlightCmp();
	UFUNCTION()
	void OnFlightInt();
	UFUNCTION()
	void OnLoad();
	UFUNCTION()
	void OnUnload();

	struct FlightDestination
	{
		FName MapName;
		FVector LongitudeLatitudeHeight;
	};
	TArray<FlightDestination> Destinations = 
	{
		FlightDestination({ "MelbourneMap", {-105.25737, 39.736401, 2250.0} }),
		FlightDestination({ "DenverMap", {39.743454, -104.988761, 1798.733479}}),
	};
	uint32_t DestinationIndex = 0;

	bool bFlying = false;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* IA_Flight;
};
