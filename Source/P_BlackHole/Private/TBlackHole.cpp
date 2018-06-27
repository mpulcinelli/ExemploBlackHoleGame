// Fill out your copyright notice in the Description page of Project Settings.

#include "TBlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATBlackHole::ATBlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;


	InnerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	InnerSphereComp->SetSphereRadius(100);
	InnerSphereComp->SetupAttachment(MeshComp);


	InnerSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATBlackHole::OverlapInnerSphere);

	OuterSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComp"));
	OuterSphereComp->SetSphereRadius(3000);
	OuterSphereComp->SetupAttachment(MeshComp);


}

// Called when the game starts or when spawned
void ATBlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATBlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void ATBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<UPrimitiveComponent*> OverlappingComps;

	OuterSphereComp->GetOverlappingComponents(OverlappingComps);

	for (int i =0 ;i<OverlappingComps.Num();i++)
	{
		UPrimitiveComponent* PrimComp = OverlappingComps[i];

		if (PrimComp && PrimComp->IsSimulatingPhysics())
		{
			const float SphereRadius = OuterSphereComp->GetScaledSphereRadius();
			const float ForceStrength = -2000;

			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}

	}

}

