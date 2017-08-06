// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AIPatrollingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALGAME_API UAIPatrollingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIPatrollingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

public:
	UPROPERTY(EditAnywhere, Category = "Movement")
		TArray< AActor* > PatrolPoints;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		TArray<AActor*> GetPatrolPoints() const;

	UPROPERTY(EditAnywhere, Category = "Movement")
		int PointIndex = 0;

};
