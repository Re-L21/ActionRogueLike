// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USInteractionComponent;
class UAnimMontage;
class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BlackHoleProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> DashProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	FTimerHandle timerHandle_PrimaryAttack;
	FTimerHandle timerHandle_BlackholeAttack;
	FTimerHandle timerHandle_Dash;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float attackAnimDelay;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* cameraComp;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* interactionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USAttributeComponent* attributeComp;

	void MoveForward(float value);
	void MoveRight(float value);

	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();

	void BlackHoleAttack();
	void BlackholeAttack_TimeElapsed();
	
	void Dash();
	void Dash_TimeElapsed();

	void SpawnProjectile(TSubclassOf<AActor> clasToSpawn);

	void PrimaryInteract();

	UFUNCTION()
	void OnHealthChanged(AActor* instigatorActor, USAttributeComponent* owningComponent, float newHealth, float delta);

	virtual void PostInitializeComponents() override;

public:	

	ASCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
