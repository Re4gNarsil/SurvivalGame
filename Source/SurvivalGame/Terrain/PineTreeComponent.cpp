// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "PineTreeComponent.h"

// Sets default values for this component's properties
UPineTreeComponent::UPineTreeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPineTreeComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < SpawnCount; i++)
	{
		if (i <= (SpawnCount / 2)) {
			FVector NewLocation = FMath::RandPointInBox(SpawnExtentsLeft);
			AddInstance(FTransform(NewLocation));
		} else {
			FVector NewLocation = FMath::RandPointInBox(SpawnExtentsRight);
			AddInstance(FTransform(NewLocation));
		}


	}

	// ...

}


// Called every frame
void UPineTreeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
