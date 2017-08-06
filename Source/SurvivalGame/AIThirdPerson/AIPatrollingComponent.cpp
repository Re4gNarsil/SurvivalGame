// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "AIPatrollingComponent.h"


// Sets default values for this component's properties
UAIPatrollingComponent::UAIPatrollingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAIPatrollingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAIPatrollingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

TArray< AActor* > UAIPatrollingComponent::GetPatrolPoints() const
{
	return PatrolPoints;
}