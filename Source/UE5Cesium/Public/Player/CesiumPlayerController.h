// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CesiumPlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class UE5CESIUM_API ACesiumPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	ACesiumPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void BeginPlay() override;

	//virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* IMC_Default;
};
