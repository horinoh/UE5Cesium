// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/ScesiumPawn.h"

#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreaming.h"

AScesiumPawn::AScesiumPawn()
{
	//!< インプットアクションのアセット
	static ConstructorHelpers::FObjectFinder<UInputAction> Flight(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Flight.IA_Flight'"));
	if (Flight.Succeeded())
	{
		IA_Flight = Flight.Object;
	}

	//!< フライトカーブのアセット
	static ConstructorHelpers::FObjectFinder<UCurveFloat> AltitudeProfileCurve(TEXT("/Script/Engine.CurveFloat'/CesiumForUnreal/Curve_AltitudeProfile_Float.Curve_AltitudeProfile_Float'"));
	if (AltitudeProfileCurve.Succeeded())
	{
		FlyToAltitudeProfileCurve = AltitudeProfileCurve.Object;
	}
	static ConstructorHelpers::FObjectFinder<UCurveFloat> ProgressCurve(TEXT("/Script/Engine.CurveFloat'/CesiumForUnreal/Curve_Progress_Float.Curve_Progress_Float'"));
	if (ProgressCurve.Succeeded())
	{
		FlyToProgressCurve = ProgressCurve.Object;
	}
	static ConstructorHelpers::FObjectFinder<UCurveFloat> MaximumAltitudeCurve(TEXT("/Script/Engine.CurveFloat'/CesiumForUnreal/Curve_MaxAltitude_Float.Curve_MaxAltitude_Float'"));
	if (MaximumAltitudeCurve.Succeeded())
	{
		FlyToMaximumAltitudeCurve = MaximumAltitudeCurve.Object;
	}

	//!< フライトのコールバック
	OnFlightComplete.AddDynamic(this, &AScesiumPawn::OnFlightCmp);
	OnFlightInterrupt.AddDynamic(this, &AScesiumPawn::OnFlightInt);
}

void AScesiumPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//!< インプットアクションをバインド
	if (auto Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (nullptr != IA_Flight)
		{
			Input->BindAction(IA_Flight, ETriggerEvent::Triggered, this, &AScesiumPawn::OnFlight);
		}
	}
}

void AScesiumPawn::OnFlight(const FInputActionInstance& Instance)
{
	if (bFlying) { return; }
	bFlying = true;

	++DestinationIndex;
	DestinationIndex %= Destinations.Num();
	const auto& Dest = Destinations[DestinationIndex];

	FlyToLocationLongitudeLatitudeHeight(Dest.LongitudeLatitudeHeight, 0.0, 0.0, false);
	
	GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::White, FString(TEXT("OnFlight to ")) + Dest.MapName.ToString());

	//auto Level = UGameplayStatics::GetStreamingLevel(GetWorld(), Dest.MapName);
	//if (nullptr != Level) 
	//{
	//	Level->SetShouldBeVisible(false);
	//	if (Level->IsLevelLoaded()) 
	//	{
	//		UGameplayStatics::UnloadStreamLevel(this, Dest.MapName, FLatentActionInfo(0, 2, TEXT("OnUnload"), this), true);
	//	}
	//}
}

void AScesiumPawn::OnFlightCmp()
{
	bFlying = false;

	GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::White, TEXT("OnFlightCmp"));

	//const auto& Dest = Destinations[DestinationIndex];
	//UGameplayStatics::LoadStreamLevel(this, Dest.MapName, true, true, FLatentActionInfo(0, 1, TEXT("OnLoad"), this));
}
void AScesiumPawn::OnFlightInt() 
{
	bFlying = false;

	GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::White, TEXT("OnFlightInt"));
}
void AScesiumPawn::OnLoad() 
{
	GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::White, TEXT("OnLoad"));

	//const auto& Dest = Destinations[DestinationIndex];
	//auto Level = UGameplayStatics::GetStreamingLevel(GetWorld(), Dest.MapName);
	//if (nullptr != Level && Level->IsLevelLoaded())
	//{
	//	Level->SetShouldBeVisible(true);
	//}
}
void AScesiumPawn::OnUnload()
{
	GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::White, TEXT("OnUnload"));
}