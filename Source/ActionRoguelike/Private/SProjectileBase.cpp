// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet//GameplayStatics.h"

// Sets default values
ASProjectileBase::ASProjectileBase()
{
	sphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	sphereComp->SetCollisionProfileName("Projectile");
	sphereComp->OnComponentHit.AddDynamic(this, &ASProjectileBase::OnActorHit);
	RootComponent = sphereComp;

	effectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	effectComp->SetupAttachment(RootComponent);

	moveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMoveComp");
	moveComp->bRotationFollowsVelocity = true;
	moveComp->bInitialVelocityInLocalSpace = true;
	moveComp->ProjectileGravityScale = 0.0f;
	moveComp->InitialSpeed = 8000;

}

void ASProjectileBase::OnActorHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	Explode();
}

void ASProjectileBase::Explode_Implementation()
{
	if (ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, impactVFX, GetActorLocation(), GetActorRotation());
		Destroy();
	}
}

void ASProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}