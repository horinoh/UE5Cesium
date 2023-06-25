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
	//!< GlobeAwareDefaultPawn ���g�p
	//DefaultPawnClass = AGlobeAwareDefaultPawn::StaticClass();
	//!< GlobeAwareDefaultPawn �p���N���X���g�p
	DefaultPawnClass = AScesiumPawn::StaticClass();
#else
	//!< DynamicPawn(BP) ���g�p
	//!< ���t�@�����X���R�s�[�œ����镶���񂩂� '' �����������o���A����� "_C" ��t�����������̂��w�肷��
	//!< "AAA'BBB.CCC'" -> "BBB.CCC_C"
	static ConstructorHelpers::FClassFinder<UObject> PawnClass(TEXT("/CesiumForUnreal/DynamicPawn.DynamicPawn_C"));
	if (PawnClass.Succeeded())
	{
		DefaultPawnClass = PawnClass.Class;
	}
#endif
}

