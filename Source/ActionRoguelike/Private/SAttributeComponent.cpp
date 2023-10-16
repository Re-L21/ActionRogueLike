// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	health = 100;

}

bool USAttributeComponent::IsAlive() const
{
	return health > 0.0f;
}

bool USAttributeComponent::ApplyHealthChange(float delta)
{
	health += delta;

	onHealthChanged.Broadcast(nullptr, this, health, delta);
	
	return true;
}
