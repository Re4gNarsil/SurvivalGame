// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CycleTheIndex.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UCycleTheIndex : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Blackboard Keys")
		struct FBlackboardKeySelector PatrolRouteIndex;
};
