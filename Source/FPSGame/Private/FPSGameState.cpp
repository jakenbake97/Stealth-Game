// Copyright Half-Way Games, All Rights Reserved.


#include "FPSGameState.h"

#include "EngineUtils.h"
#include "FPSPlayerController.h"

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Get());
		if(PC && PC->IsLocalController())
		{
			PC->OnMissionCompleted(InstigatorPawn, bMissionSuccess);

			APawn* MyPawn = PC->GetPawn();
			if(MyPawn)
			{}
			MyPawn->DisableInput(PC);
		}
	}
}
