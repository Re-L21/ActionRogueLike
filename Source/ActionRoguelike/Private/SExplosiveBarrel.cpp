// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include <DrawDebugHelpers.h>

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	meshComponent->SetSimulatePhysics(true);
	meshComponent->SetCollisionProfileName("PhysicsActor");
	RootComponent = meshComponent;

	forceComponent = CreateDefaultSubobject<URadialForceComponent>("ForceComponent");
	forceComponent->SetupAttachment(meshComponent);

	forceComponent->SetAutoActivate(false);

	forceComponent->Radius = 750.0f;
	forceComponent->ImpulseStrength = 2500.0f;
	forceComponent->bImpulseVelChange = true;

	forceComponent->AddCollisionChannelToAffect(ECC_WorldDynamic);

}

void ASExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	meshComponent->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActionHit);
}

void ASExplosiveBarrel::OnActionHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit)
{
	forceComponent->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("OnActorHit in Explosive Barrel"));

	// %s = string
	// %f = float
	// logs: "OtherActor: MyActor_1, at gametime: 124.4"
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *GetNameSafe(otherActor), GetWorld()->TimeSeconds);

	FString combinedString = FString::Printf(TEXT("Hit at location: %s"), *hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), hit.ImpactPoint, combinedString, nullptr, FColor::Green, 2.0f, true);


}


