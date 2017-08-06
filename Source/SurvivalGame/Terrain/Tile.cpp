// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "GrassComponent.h"
#include "../AIThirdPerson/TP_AICharacter.h"
#include "../AIThirdPerson/AIPatrollingComponent.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SpawnStuff()
{
	if (!ensure(ObstaclesBlueprint.GetData())) { return; }
	int Amount = FMath::RandRange(16, 24);
	FRotator SpawnRotation;  //OUT parameters for FindSpace;
	FVector SpawnLocation;

	for (int i = 0; i < Amount; i++)
	{
		int Chosen = FMath::RandRange(0, ObstaclesBlueprint.Num() - 1);
		if (ensure(ObstaclesBlueprint[Chosen])) {
			float ScaleTo = FCString::Atof(*(ObstaclesBlueprint[Chosen].GetDefaultObject()->Tags[1].ToString()));
			float OurScale = 1.f;
			if (ScaleTo > 1) { OurScale = FMath::RandRange(1.f, ScaleTo); }
			else if (ScaleTo < 1) { OurScale = FMath::RandRange(ScaleTo, 1.f); }

			float Size = FCString::Atof(*(ObstaclesBlueprint[Chosen].GetDefaultObject()->Tags[0].ToString())) * OurScale;
			if (FindSpace(SpawnLocation, SpawnRotation, Size)) { SpawnActor(SpawnLocation, SpawnRotation, Chosen, OurScale); }
		}
	}
}

bool ATile::FindSpace(FVector &Location, FRotator &Rotation, float Size)
{
	for (int i = 0; i < 10; i++){
		FVector NewLocation = FMath::RandPointInBox(FBox(FVector(-1700, -1700, 50), FVector(1700, 1700, 50)));
		
		if (!SphereCast(this->GetActorLocation() + NewLocation, Size)) {
			Location = NewLocation;
			Rotation = FRotator(0, FMath::RandRange(0.f, 360.f), 0);
			return true;
		}
	}
	return false;
}

bool ATile::SphereCast(FVector Location, float Radius)
{
	FHitResult HitResult;
	bool Hit = GetWorld()->SweepSingleByChannel(HitResult, Location, Location, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
	return Hit;
}

void ATile::SpawnActor(FVector NewLocation, FRotator NewRotation, int Obstacle, float Scale)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ObstaclesBlueprint[Obstacle]);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRelativeLocation(NewLocation);
	Spawned->SetActorRotation(NewRotation);
	Spawned->SetActorScale3D(Spawned->GetActorScale3D() * Scale);
}

ATP_AICharacter* ATile::SpawnGuard(float OurExtraHealth)
{
	if (!ensure(GuardBlueprint)) { return nullptr; }
	FRotator SpawnRotation;  //OUT parameters for FindSpace;
	FVector SpawnLocation;
	ATP_AICharacter* Guard;
TryAgain:
	if (FindSpace(SpawnLocation, SpawnRotation, 280)) {
		Guard = GetWorld()->SpawnActor<ATP_AICharacter>(GuardBlueprint);
		Guard->SetActorLocation(this->GetActorLocation() + SpawnLocation + FVector(0, 0, 110.f));
		Guard->Tags.Add(FName("Guard"));
		Guard->InitialHealth += OurExtraHealth;
		Guards.Add(Guard);
	}
	else { goto TryAgain; }
	return Guard;
}

AActor* ATile::RandomlyChoosePoint(UAIPatrollingComponent * Patrol)
{
	TArray < AActor* > SceneObjects; //OUT parameter for GetAttachedActors
	this->GetAttachedActors(SceneObjects);
	if (Patrol->PatrolPoints.GetData()) {
		for (int i = 0; i < 100; i++)
		{
			int RandomPointer = FMath::RandRange(0, (SceneObjects.Num() - 1));
			if (NoSimilarObjects(Patrol, SceneObjects[RandomPointer])) { return SceneObjects[RandomPointer]; }
		}
	}
	return SceneObjects[0];
}

bool ATile::NoSimilarObjects(UAIPatrollingComponent * Patrol, AActor* ObjectToCheck)
{
	for (int i = 0; i < Patrol->PatrolPoints.Num(); i++)
	{
		if (Patrol->PatrolPoints[i] == ObjectToCheck) { return false; }
	}
	return true;
}

void ATile::AssignGuards()
{
	for (int i = 0; i < Guards.Num(); i++)
	{
		UAIPatrollingComponent* OurPatrol = Guards[i]->FindComponentByClass<UAIPatrollingComponent>();
		//UE_LOG(LogTemp, Warning, TEXT("Comp %s"), *OurPatrol->GetFullName());
		int NumberOfPoints = FMath::RandRange(3, 6);
		for (int n = 0; n < NumberOfPoints; n++)
		{
			OurPatrol->PatrolPoints.Add(RandomlyChoosePoint(OurPatrol));
		}
	}
}

bool ATile::CheckForGuards(UBoxComponent* LockBox)
{
	TArray < AActor* > Players;
	LockBox->GetOverlappingActors(Players, TSubclassOf< ATP_AICharacter >());
	for (int i = 0; i < Players.Num() - 1; i++)
	{
		if (Cast<ATP_AICharacter>(Players[i])) {
			if (Cast<ATP_AICharacter>(Players[i])->GetController()) {
				if (!Cast<ATP_AICharacter>(Players[i])->IsPlayerControlled()) { return true; }
			}
		}
	}
	return false;
}


void ATile::SpawnSupplyPacks(int NumOfPacks, TArray< AActor* > &HealthPacks, TArray< AActor* > &AmmoPacks)
{
	if (!ensure(SuppliesBlueprint.GetData())) { return; }
	for (int i = 0; i < SuppliesBlueprint.Num(); i++)
	{
		int Amount;
		if (i == 0) { Amount = FMath::RandRange(NumOfPacks - 1, NumOfPacks + 1); }
		else { Amount = FMath::RandRange(NumOfPacks, NumOfPacks + 2); }

		FRotator SpawnRotation;  //OUT parameters for FindSpace;
		FVector SpawnLocation;
		for (int n = 0; n < Amount; n++)
		{
			if (ensure(SuppliesBlueprint[i])) {
				if (FindSpace(SpawnLocation, SpawnRotation, 60)) {
					AActor* Pack = GetWorld()->SpawnActor<AActor>(SuppliesBlueprint[i]);
					Pack->SetActorRelativeLocation(this->GetActorLocation() + SpawnLocation);
					Pack->SetActorRotation(SpawnRotation);
					if (i == 0) { HealthPacks.Add(Pack); }
					else if (i == 1) { AmmoPacks.Add(Pack); }
				}
			}
		}
	}
}
