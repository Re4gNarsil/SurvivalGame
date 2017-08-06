// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "RockGroup.h"


// Sets default values
ARockGroup::ARockGroup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARockGroup::BeginPlay()
{
	Super::BeginPlay();

	TArray< USceneComponent* > Rocks;
	RootComponent->GetChildrenComponents(true, Rocks);

	for (int i = 0; i < Rocks.Num() - 1; i++)
	{
		FBox SpawnLimits = FBox(FVector(-200, -200, -20), FVector(200, 200, 20));
		Rocks[i]->SetRelativeLocation(FMath::RandPointInBox(SpawnLimits));

		FRotator NewRotation = FRotator(FMath::RandRange(0.f, 360.f), FMath::RandRange(0.f, 360.f), FMath::RandRange(0.f, 360.f));
		Rocks[i]->SetWorldRotation(NewRotation);

		FVector NewScale = FVector(FMath::RandRange(0.75, 3.f), FMath::RandRange(0.75f, 3.f), FMath::RandRange(0.75f, 3.f));
		Rocks[i]->SetWorldScale3D(NewScale);
	}
	
}

// Called every frame
void ARockGroup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

