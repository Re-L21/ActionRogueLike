// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGameplayInterface.h"
#include <DrawDebugHelpers.h>

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void USInteractionComponent::PrimaryInteract()
{
	float radius = 30.0f;

	FCollisionObjectQueryParams objectQueryParams;
	objectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* myOwner = GetOwner();

	FVector eyeLocation;
	FRotator eyeRotation;

	myOwner->GetActorEyesViewPoint(eyeLocation, eyeRotation);

	FVector end = eyeLocation + (eyeRotation.Vector() * 1000);

	//FHitResult hit;
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(hit, eyeLocation, end, objectQueryParams);

	TArray<FHitResult> hits;

	FCollisionShape shape;
	shape.SetSphere(radius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(hits, eyeLocation, end, FQuat::Identity, objectQueryParams, shape);

	FColor lineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult hit : hits)
	{
		AActor* hitActor = hit.GetActor();
		if (hitActor)
		{
			if (hitActor->Implements<USGameplayInterface>())
			{
				APawn* myPawn = Cast<APawn>(myOwner);

				ISGameplayInterface::Execute_Interact(hitActor, myPawn);
				break;
			}
		}
		DrawDebugSphere(GetWorld(), hit.ImpactPoint, radius, 32, lineColor, false, 2.0f);
	}

	DrawDebugLine(GetWorld(), eyeLocation, end, lineColor, false, 2.0f, 0, 2.0f);

}