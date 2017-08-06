// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SurvivalGameProjectile.h"
#include "TP_AICharacter.generated.h"

class ASurvivalGameGun;
class UAIPatrollingComponent;

UCLASS()
class SURVIVALGAME_API ATP_AICharacter : public ACharacter
{
	GENERATED_BODY()

		/** Pawn mesh: 1st person view (arms; seen only by self) */
		UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		class USkeletalMeshComponent* Mesh1P;

		/** First person camera */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

		/** Pawn mesh: 1st person view (arms; seen only by self) */
		UPROPERTY(EditAnywhere, Category = "Patrolling")
		class UAIPatrollingComponent* PatrolComponent;

public:

	// Sets default values for this character's properties
	ATP_AICharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/** Call this function to detach safely pawn from its controller, knowing that we will be destroyed soon.	 */
	//virtual void DetachFromControllerPendingDestroy() override;
	//virtual void UnPossessed() override;

	//called just before OnPendingDestroy if we are player controlled
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void ReattachGun();

	/** Weapon class to spawn */
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class ASurvivalGameGun> WeaponBlueprint;

	/** AnimMontage to play each time we fire (1st person)*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	class UAnimMontage* FireAnimationFP;

	/** AnimMontage to play each time we fire (3rd person)*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	class UAnimMontage* FireAnimationTP;

	/** Gives a command to fire a projectile. */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void PullTrigger();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool RefillAmmoOnHand(int AmmoRefill);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int InitialAmmoOnHand = 40;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
	int ExtraAmmo = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float InitialHealth = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int CurrentAmmoOnHand;

private:

	ASurvivalGameGun* OurGun;

	UAnimInstance* AnimInstanceFP;

	UAnimInstance* AnimInstanceTP;

};
