// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "AIChooseNextPoint.h"
#include "AIController.h"
#include "AIPatrollingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UAIChooseNextPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the patrol route; make sure we have the necessary things to do so
	if (OwnerComp.GetAIOwner()->GetPawn()) { UE_LOG(LogTemp, Warning, TEXT("Owner is "), *OwnerComp.GetAIOwner()->GetPawn()->GetName()); }
	else { UE_LOG(LogTemp, Warning, TEXT("AI Owner is missing")); }
	if (OwnerComp.GetOwner()) { UE_LOG(LogTemp, Warning, TEXT("Owner is "), *OwnerComp.GetOwner()->GetName()); }
	else { UE_LOG(LogTemp, Warning, TEXT("Owner is missing")); }
	return EBTNodeResult::Failed;

	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ensure(ControlledPawn)) {
		UE_LOG(LogTemp, Warning, TEXT("No Guard"));
		return EBTNodeResult::Failed;
	}
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UAIPatrollingComponent>();
	if (!ensure(PatrolRoute)) { 
		UE_LOG(LogTemp, Warning, TEXT("Guard is missing AIPatrollingComponent")); 
		return EBTNodeResult::Failed;
	}

	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() < 1) { UE_LOG(LogTemp, Warning, TEXT("Guard is missing his Patrol Points"));	}

	// Set next point to go to
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(PatrolRouteIndex.SelectedKeyName);
	if (PatrolPoints.IsValidIndex(Index)) {
		BlackboardComp->SetValueAsObject(NextPoint.SelectedKeyName, PatrolPoints[Index]);
		return EBTNodeResult::Succeeded;
	} 
	else { UE_LOG(LogTemp, Warning, TEXT("Index reference is not valid")); }
	return EBTNodeResult::Failed;
}


