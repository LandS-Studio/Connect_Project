// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "NativeGameplayTags.h"
#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "EEC_SetDefaultValues.generated.h"


UE_DECLARE_GAMEPLAY_TAG_EXTERN(VALUE_HEALTH);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(VALUE_MAX_HEALTH);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(VALUE_ARMOR);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(VALUE_MAX_ARMOR);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(VALUE_SPEED);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(VALUE_DEFAULT_SPEED);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(VALUE_POWER_DAMAGE);

/**
 * 
 */
UCLASS()
class TPPROJECT_API UEEC_SetDefaultValues : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
