// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame.h"
#include "CycleTheIndex.h"
#include "AIController.h"
#include "AIPatrollingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UCycleTheIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the patrol route; make sure we have the necessary things to do so
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UAIPatrollingComponent>();
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();

	// Set next point to go to
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(PatrolRouteIndex.SelectedKeyName);
	if (PatrolPoints.IsValidIndex(Index)) {
		// Cycle the index
		auto NextIndex = (Index + 1) % PatrolPoints.Num();
		BlackboardComp->SetValueAsInt(PatrolRouteIndex.SelectedKeyName, NextIndex);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
