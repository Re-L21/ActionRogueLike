// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASDashProjectile : public ASProjectileBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float teleportDelay;
	
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float detonateDelay;

	FTimerHandle timerHandle_DelayedDetonate;

	virtual void Explode_Implementation() override;

	virtual void BeginPlay() override;

	void TeleportInstigator();

public:

	ASDashProjectile();


};
