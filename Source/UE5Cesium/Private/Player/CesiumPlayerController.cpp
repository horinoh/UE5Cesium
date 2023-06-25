// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CesiumPlayerController.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

ACesiumPlayerController::ACesiumPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Default.IMC_Default'"));
	if (IMC.Succeeded())
	{
		IMC_Default = IMC.Object;
	}
}

void ACesiumPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr != IMC_Default)
	{
		if (const auto LP = GetLocalPlayer())
		{
			if (auto InputSystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->AddMappingContext(IMC_Default, 0);
			}
		}
	}
}

//void ACesiumPlayerController::SetupInputComponent() 
//{
//	PlayerInput;
//}