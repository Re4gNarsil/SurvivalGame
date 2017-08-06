// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SurvivalGameGun.generated.h"

UCLASS()
class SURVIVALGAME_API ASurvivalGameGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASurvivalGameGun();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Gun mesh */
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		class USceneComponent* FP_MuzzleLocation;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		TSubclassOf<class ASurvivalGameProjectile> ProjectileBlueprint;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		class UAnimMontage* FireAnimation;

	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool OnFire();

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float TimeToReload = .05f;

private:
	float ReloadTime = 0.f;
};
