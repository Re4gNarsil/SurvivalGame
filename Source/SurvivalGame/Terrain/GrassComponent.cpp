// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "GrassComponent.h"


// Sets default values for this component's properties
UGrassComponent::UGrassComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrassComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < SpawnCount; i++)
	{
		FVector NewLocation = FMath::RandPointInBox(SpawnExtents);
		AddInstance(FTransform(NewLocation));

	}

	// ...
	
}


// Called every frame
void UGrassComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

