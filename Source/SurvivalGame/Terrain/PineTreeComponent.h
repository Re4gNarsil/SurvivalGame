// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "PineTreeComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVALGAME_API UPineTreeComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPineTreeComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		FBox SpawnExtentsLeft;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		FBox SpawnExtentsRight;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int SpawnCount;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



};
