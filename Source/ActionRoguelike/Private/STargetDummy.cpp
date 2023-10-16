// Fill out your copyright notice in the Description page of Project Settings.


#include "STargetDummy.h"
#include "Components/StaticMeshComponent.h"
#include "SAttributeComponent.h"

// Sets default values
ASTargetDummy::ASTargetDummy()
{
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = meshComp;

	attributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	attributeComp->onHealthChanged.AddDynamic(this, &ASTargetDummy::OnHealthChanged);
}

void ASTargetDummy::OnHealthChanged(AActor* instigatorActor, USAttributeComponent* owningComponent, float newHealth, float delta)
{
	if (delta < 0.0f)
	{
		meshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);

	}
}


