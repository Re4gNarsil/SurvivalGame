// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UGrassComponent;
class ATP_AICharacter;
class UAIPatrollingComponent;

UCLASS()
class SURVIVALGAME_API ATile : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void SpawnStuff();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void SpawnSupplyPacks(int NumOfPacks, TArray< AActor* > &HealthPacks, TArray< AActor* > &AmmoPacks);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	ATP_AICharacter* SpawnGuard(float OurExtraHealth);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void AssignGuards();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool CheckForGuards(UBoxComponent * LockBox);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	TArray< TSubclassOf<class AActor> > ObstaclesBlueprint;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	TSubclassOf<class ATP_AICharacter> GuardBlueprint;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	TArray< TSubclassOf<class AActor> > SuppliesBlueprint;

private:
	bool SphereCast(FVector Location, float Radius);

	void SpawnActor(FVector NewLocation, FRotator NewRotation, int Obstacle, float Scale);

	AActor* RandomlyChoosePoint(UAIPatrollingComponent* Patrol);

	bool NoSimilarObjects(UAIPatrollingComponent * Patrol, AActor* ObjectToCheck);

	bool FindSpace(FVector &Location, FRotator &Rotation, float Size);

	TArray< AActor* > Guards;

};
