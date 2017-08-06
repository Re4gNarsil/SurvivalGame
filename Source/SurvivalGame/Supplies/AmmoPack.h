// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AmmoPack.generated.h"

UCLASS()
class SURVIVALGAME_API AAmmoPack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoPack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	int OurAmmo = 10;

	/** Gives a command to fire a projectile. */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	int GetOurAmmo();
	
};
