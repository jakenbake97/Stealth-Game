// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"

#include "FPSGameState.h"
#include "FPSHUD.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn)
	{
		if (SpectatingViewpointClass)
		{
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

			AActor* NewViewTarget = nullptr;

			// Change viewtarget if any valid actor is found
			if (ReturnedActors.Num() > 0)
			{
				NewViewTarget = ReturnedActors[0];

				for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
				{
					APlayerController* PlayerController = It->Get();
					if (PlayerController)
					{
						PlayerController->SetViewTargetWithBlend(NewViewTarget, 0.5f, VTBlend_Cubic);
					}
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is null. Please update GameMode class with valid subclass. Cannot change spectating view target"))
		}
	}

	AFPSGameState* GS = GetGameState<AFPSGameState>();
	if (GS)
	{
		GS->MulticastOnMissionComplete(InstigatorPawn, bMissionSuccess);
	}

	OnMissionCompleted(InstigatorPawn, bMissionSuccess);
}
