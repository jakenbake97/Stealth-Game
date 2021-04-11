// Copyright Half-Way Games, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:

	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerController")
	void OnMissionCompleted(APawn* InstigatorPawn, bool bIsMissionSuccess);
};
