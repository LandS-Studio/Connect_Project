// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"
#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "EEC_SetDefaultWeaponValues.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(VALUE_AMMO);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(VALUE_MAX_AMMO);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(VALUE_WEAPON_DAMAGE);

/**
 * 
 */
UCLASS()
class TPPROJECT_API UEEC_SetDefaultWeaponValues : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
