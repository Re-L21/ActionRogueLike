// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS(ABSTRACT) // 'ABSTRACT' mark this class as incomplete, keeping this out of certain dropdowns windows like SpawnActor in Unreal Engine
class ACTIONROGUELIKE_API ASProjectileBase : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* impactVFX;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* sphereComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* moveComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* effectComp;

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	virtual void PostInitializeComponents() override;
	
public:	

	ASProjectileBase();

};
