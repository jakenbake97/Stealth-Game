// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"

#include "Components/SphereComponent.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	GravitySphere = CreateDefaultSubobject<USphereComponent>(TEXT("GravitySphere"));
	GravitySphere->SetupAttachment(MeshComp);

	SingularitySphere = CreateDefaultSubobject<USphereComponent>(TEXT("SingularitySphere"));
	SingularitySphere->SetupAttachment(MeshComp);
}

void ABlackHole::OverlapSingularity(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
	SingularitySphere->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapSingularity);
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> ObjectsInRange;
	GravitySphere->GetOverlappingComponents(ObjectsInRange);
	for (auto Object : ObjectsInRange)
	{
		if (Object && Object->IsSimulatingPhysics())
		{
			Object->AddRadialForce(GetActorLocation(), GravitySphere->GetScaledSphereRadius(), -GravityStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}

