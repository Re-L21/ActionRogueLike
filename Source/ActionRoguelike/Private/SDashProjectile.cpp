// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ASDashProjectile::ASDashProjectile()
{
	teleportDelay = 0.2f;
	detonateDelay = 0.2f;

	moveComp->InitialSpeed = 6000.0f;

}

void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(timerHandle_DelayedDetonate, this, &ASDashProjectile::Explode, detonateDelay);
}


void ASDashProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(timerHandle_DelayedDetonate);

	UGameplayStatics::SpawnEmitterAtLocation(this, impactVFX, GetActorLocation(), GetActorRotation());

	effectComp->DeactivateSystem();

	moveComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle timerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(timerHandle_DelayedTeleport, this, &ASDashProjectile::TeleportInstigator, teleportDelay);

}

void ASDashProjectile::TeleportInstigator()
{
	AActor* actorToTeleport = GetInstigator();
	if (ensure(actorToTeleport))
	{
		actorToTeleport->TeleportTo(GetActorLocation(), actorToTeleport->GetActorRotation(), false, false);
	}
}

