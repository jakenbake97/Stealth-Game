// Copyright Half-Way Games, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

class UBoxComponent;

UCLASS()
class FPSGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* ArrowComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Effect")
	float LaunchStrength = 1500;

	UPROPERTY(EditAnywhere, Category = "Effect")
	float LaunchPitchAngle = 35;

	UPROPERTY(EditDefaultsOnly, Category="Effect")
	UParticleSystem* LaunchFX;

	UFUNCTION()
    void RespondToOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
