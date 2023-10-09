// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	meshComponent->SetSimulatePhysics(true);
	RootComponent = meshComponent;

	forceComponent = CreateDefaultSubobject<URadialForceComponent>("ForceComponent");
	forceComponent->SetupAttachment(meshComponent);

	forceComponent->SetAutoActivate(false);

	forceComponent->Radius = 750.0f;
	forceComponent->ImpulseStrength = 2500.0f;
	forceComponent->bImpulseVelChange = true;

	forceComponent->AddCollisionChannelToAffect(ECC_WorldDynamic);
	//meshComponent->OnComponentHit.AddDynamic(this, ASExplosiveBarrel::OnActorHit);

}

void ASExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	meshComponent->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActionHit);
}

void ASExplosiveBarrel::OnActionHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit)
{
	forceComponent->FireImpulse();
}


