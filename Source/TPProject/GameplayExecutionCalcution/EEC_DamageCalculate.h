// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "NativeGameplayTags.h"
#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "EEC_DamageCalculate.generated.h"


UE_DECLARE_GAMEPLAY_TAG_EXTERN(VALUE_DAMAGE);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(STATUS_INVINSIBILITY);

/**
 * 
 */
UCLASS()
class TPPROJECT_API UEEC_DamageCalculate : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
