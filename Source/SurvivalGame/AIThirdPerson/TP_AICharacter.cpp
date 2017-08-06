// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "SurvivalGameProjectile.h"
#include "TP_AICharacter.h"
#include "SurvivalGameGun.h"
#include "AIPatrollingComponent.h"
#include "Animation/AnimInstance.h"
#include "MyPlayerController.h"

// Sets default values
ATP_AICharacter::ATP_AICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-59.3f, -3.0f, 62.8); // Position the camera
	FirstPersonCameraComponent->RelativeRotation = FRotator(-10.f, 0.f, 0.f);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(8.8f, -18.0f, 0.8f);
	Mesh1P->RelativeLocation = FVector(55.3f, 17.6f, -172.5f);

	PatrolComponent = CreateDefaultSubobject<UAIPatrollingComponent>(TEXT("PatrolComponent"));

}

// Called when the game starts or when spawned
void ATP_AICharacter::BeginPlay()
{
	Super::BeginPlay();

	OurGun = GetWorld()->SpawnActor<ASurvivalGameGun>(WeaponBlueprint);
	if (IsPlayerControlled()) { 
		InitialAmmoOnHand += ExtraAmmo;
		OurGun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); 
		Cast<AMyPlayerController>(GetController())->OurAmmo = CurrentAmmoOnHand;
	}
	else { OurGun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); }

	// Get the animation object for the arms and body meshes
	AnimInstanceFP = Mesh1P->GetAnimInstance();
	AnimInstanceTP = GetMesh()->GetAnimInstance();
	if (InputComponent != NULL) { InputComponent->BindAction("Fire", IE_Pressed, this, &ATP_AICharacter::PullTrigger); }

	CurrentAmmoOnHand = InitialAmmoOnHand;
}

// Called every frame
void ATP_AICharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ATP_AICharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATP_AICharacter::ReattachGun()
{
	if (IsPlayerControlled()) { OurGun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); }
}

//void ATP_AICharacter::DetachFromControllerPendingDestroy()
//{
//	Super::DetachFromControllerPendingDestroy();
//}

//void ATP_AICharacter::UnPossessed()
//{
//	Super::UnPossessed();
//
//	//OurGun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint_0"));
//}

void ATP_AICharacter::PullTrigger()
{
	//Pass a command to OurGun to fire
	if (CurrentAmmoOnHand <= 0) { return; }
	if (OurGun->OnFire()) {
		//only try to play animations if we actually fired a shot

		// try and play a 1st person firing animation if specified
		if (FireAnimationFP != NULL && AnimInstanceFP != NULL)
		{
			AnimInstanceFP->Montage_Play(FireAnimationFP, 1.f);
		}

		// try and play a 3rd person firing animation if specified
		if (FireAnimationTP != NULL && AnimInstanceTP != NULL)
		{
			AnimInstanceTP->Montage_Play(FireAnimationTP, 1.f);
		}
	}
	CurrentAmmoOnHand--;
	//if (IsPlayerControlled()) { Cast<AMyPlayerController>() }
	if (IsPlayerControlled()) { Cast<AMyPlayerController>(GetController())->OurAmmo = CurrentAmmoOnHand; }
}

bool ATP_AICharacter::RefillAmmoOnHand(int AmmoRefill)
{
	if (CurrentAmmoOnHand < InitialAmmoOnHand)
	{
		CurrentAmmoOnHand += AmmoRefill;
		if (CurrentAmmoOnHand > InitialAmmoOnHand) { CurrentAmmoOnHand = InitialAmmoOnHand; }
		if (IsPlayerControlled()) { Cast<AMyPlayerController>(GetController())->OurAmmo = CurrentAmmoOnHand; }
		return true;
	}
	return false;
}
