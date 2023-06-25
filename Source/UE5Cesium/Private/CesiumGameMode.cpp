// Fill out your copyright notice in the Description page of Project Settings.


#include "CesiumGameMode.h"

#include "Player/CesiumPlayerController.h"

//#include "GlobeAwareDefaultPawn.h"
#include "Pawn/ScesiumPawn.h"

ACesiumGameMode::ACesiumGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = ACesiumPlayerController::StaticClass();

#if true
	//!< GlobeAwareDefaultPawn を使用
	//DefaultPawnClass = AGlobeAwareDefaultPawn::StaticClass();
	//!< GlobeAwareDefaultPawn 継承クラスを使用
	DefaultPawnClass = AScesiumPawn::StaticClass();
#else
	//!< DynamicPawn(BP) を使用
	//!< リファレンスをコピーで得られる文字列から '' 内だけ抜き出し、さらに "_C" を付け加えたものを指定する
	//!< "AAA'BBB.CCC'" -> "BBB.CCC_C"
	static ConstructorHelpers::FClassFinder<UObject> PawnClass(TEXT("/CesiumForUnreal/DynamicPawn.DynamicPawn_C"));
	if (PawnClass.Succeeded())
	{
		DefaultPawnClass = PawnClass.Class;
	}
#endif
}

