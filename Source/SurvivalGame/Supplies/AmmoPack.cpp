// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "AmmoPack.h"


// Sets default values
AAmmoPack::AAmmoPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAmmoPack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmoPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AAmmoPack::GetOurAmmo()
{
	return FMath::RoundToInt(FCString::Atof(*this->Tags[0].ToString()));
}

