// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "SAttributeComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	springArmComp->bUsePawnControlRotation = true;
	springArmComp->SetupAttachment(RootComponent);

	cameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	cameraComp->SetupAttachment(springArmComp);

	interactionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	attributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	attackAnimDelay = 0.2f;

}


void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	attributeComp->onHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("JumpAction", IE_Pressed, this, &ASCharacter::Jump);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &ASCharacter::BlackHoleAttack);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ASCharacter::Dash);

	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);

}

void ASCharacter::MoveForward(float value)
{
	FRotator controlRot = GetControlRotation();
	controlRot.Pitch = 0.0f;
	controlRot.Roll = 0.0f;

	AddMovementInput(controlRot.Vector(), value);
}

void ASCharacter::MoveRight(float value)
{
	FRotator controlRot = GetControlRotation();
	controlRot.Pitch = 0.0f;
	controlRot.Roll = 0.0f;

	// X = forward (red)
	// Y = right (green)
	// Z = up (blue)

	FVector rightVector = FRotationMatrix(controlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(rightVector, value);
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(timerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, attackAnimDelay);

}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(ProjectileClass);

}

void ASCharacter::BlackHoleAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(timerHandle_BlackholeAttack, this, &ASCharacter::BlackholeAttack_TimeElapsed, attackAnimDelay);
}

void ASCharacter::BlackholeAttack_TimeElapsed()
{
	SpawnProjectile(BlackHoleProjectileClass);
}

void ASCharacter::Dash()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(timerHandle_BlackholeAttack, this, &ASCharacter::Dash_TimeElapsed, attackAnimDelay);
}

void ASCharacter::Dash_TimeElapsed()
{
	SpawnProjectile(DashProjectileClass);
}

void ASCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if (ensureAlways(ClassToSpawn))
	{
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;
		FHitResult Hit;
		FVector TraceStart = cameraComp->GetComponentLocation();
		// endpoint far into the look-at distance (not too far, still adjust somewhat towards crosshair on a miss)
		FVector TraceEnd = cameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 5000);

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		// Ignore Player
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FRotator ProjRotation;
		// true if we got to a blocking hit (Alternative: SweepSingleByChannel with ECC_WorldDynamic)
		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
		{
			// Adjust location to end up at crosshair look-at
			ProjRotation = FRotationMatrix::MakeFromX(Hit.ImpactPoint - HandLocation).Rotator();
		}
		else
		{
			// Fall-back since we failed to find any blocking hit
			ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();
		}


		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);
	}
}

void ASCharacter::PrimaryInteract()
{
	if (interactionComp)
	{
		interactionComp->PrimaryInteract();

	}
}

void ASCharacter::OnHealthChanged(AActor* instigatorActor, USAttributeComponent* owningComponent, float newHealth, float delta)
{
	if (newHealth <= 0.0f && delta < 0.0f)
	{
		APlayerController* pc = Cast <APlayerController>(GetController());
		DisableInput(pc);
	}

}
