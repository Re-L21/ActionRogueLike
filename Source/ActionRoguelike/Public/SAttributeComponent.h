// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, instigatorActor, USAttributeComponent*, owningComp, float, newHealth, float, delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

protected:

	// EditAnywhere = edit in BP editor and pre instance in level.
	// VisibleAnywhere = 'Read-Only' in editor and level. (Use for components)
	// EdtDefaultsOnly = hide variable per-instance, edit in BP editor only
	// VisibleDefaultsOnly = 'Read-Only' access for variable, only in BP editor (uncommon)
	// EditInstanceOnly = allow only editing of instance (eg. when placed in level)
	// --
	// BlueprintReadOnly = read-only in Bluprint scripting (does not affect 'details'-panel)
	// BlueprintReadWrite = read-write access in Blueprint
	// --
	// Categoory = "" - display only for detail panels and blueprint context menu

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float health;

public:	

	UPROPERTY(BlueprintAssignAble)
	FOnHealthChanged onHealthChanged;

	UFUNCTION(BlueprintCallable, Category= "Attribute")
	bool ApplyHealthChange(float delta);

};
