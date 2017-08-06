// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HealthPack.generated.h"

UCLASS()
class SURVIVALGAME_API AHealthPack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	float OurHealth = 10.f;

	/** Gives a command to fire a projectile. */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	float GetOurHealth();
	
};
