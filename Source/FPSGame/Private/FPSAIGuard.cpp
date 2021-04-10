// Copyright Half-Way Games, All Rights Reserved.


#include "FPSAIGuard.h"

#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);

	OriginalRotation = GetActorRotation();
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr) return;
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32, 12, FColor::Yellow, false, 10);

	AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->CompleteMission(SeenPawn, false);
	}

	SetGuardState(EAIState::Alerted);
}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if (GuardState == EAIState::Alerted)
	{
		return;
	}
	
	DrawDebugSphere(GetWorld(), Location, 32, 12, FColor::Emerald, false, 10);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator LookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	LookAt.Pitch = LookAt.Roll = 0;

	SetActorRotation(LookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);

	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrientation, 3.0f);

	SetGuardState(EAIState::Suspicious);
}

void AFPSAIGuard::SetGuardState(EAIState NewState)
{
	if (GuardState == NewState) return;

	GuardState = NewState;

	OnStateChanged(GuardState);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSAIGuard::ResetOrientation()
{
	if (GuardState == EAIState::Alerted)
	{
		return;
	}
	
	SetActorRotation(OriginalRotation);

	SetGuardState(EAIState::Idle);
}
