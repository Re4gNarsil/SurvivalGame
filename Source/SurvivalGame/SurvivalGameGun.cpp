// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "SurvivalGameGun.h"
#include "SurvivalGameProjectile.h"
#include "Animation/AnimInstance.h"

// Sets default values
ASurvivalGameGun::ASurvivalGameGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	RootComponent = FP_Gun;

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.0f, 75.0f, 12.0f));
	FP_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	// Default offset from the character location for projectiles to spawn
	//GunOffset = FVector(100.0f, 30.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

}

// Called when the game starts or when spawned
void ASurvivalGameGun::BeginPlay()
{
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	
	//this->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	//FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

// Called every frame
void ASurvivalGameGun::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	ReloadTime += GetWorld()->DeltaTimeSeconds;
}

bool ASurvivalGameGun::OnFire()
{
	if (ReloadTime >= TimeToReload) {
		// try and fire a projectile
		if (ProjectileBlueprint != NULL)
		{
			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				if (FP_MuzzleLocation) {
					const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();
					// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
					const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();

					// spawn the projectile at the muzzle
					World->SpawnActor<ASurvivalGameProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation);
				}
				else { UE_LOG(LogTemp, Warning, TEXT("No Muzzle Component Found")); }
			}
		}
		else { UE_LOG(LogTemp, Warning, TEXT("No Projectile Found")); }
		if (!FP_Gun) { UE_LOG(LogTemp, Warning, TEXT("No Gun Found")); }
		// try and play the sound if specified
		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}
		ReloadTime = 0.f;
		return true;
	}
	return false;
}