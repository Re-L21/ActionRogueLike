// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "SAttributeComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	sphereComp->SetCollisionProfileName("Projectile");
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
	RootComponent = sphereComp;

	effectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	effectComp->SetupAttachment(sphereComp);

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	movementComp->InitialSpeed = 1000.0f;
	movementComp->bRotationFollowsVelocity = true;
	movementComp->bInitialVelocityInLocalSpace = true;

}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherActor)
	{
		USAttributeComponent* attributeComp = Cast<USAttributeComponent>(otherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (attributeComp)
		{
			attributeComp->ApplyHealthChange(-20.0f);
			
			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

