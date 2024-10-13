// Fill out your copyright notice in the Description page of Project Settings.


#include "EEC_SetDefaultValues.h"

#include "AbilitySystemComponent.h"
#include "TPProject/GameplayerAttributes/AS_DamageAttributeSet.h"
#include "TPProject/GameplayerAttributes/AS_MovementAttributeSet.h"
#include "TPProject/GameplayerAttributes/AS_VitalAttributeSet.h"

UE_DEFINE_GAMEPLAY_TAG(VALUE_HEALTH, "Value.Health");
UE_DEFINE_GAMEPLAY_TAG(VALUE_MAX_HEALTH, "Value.MaxHealth");
UE_DEFINE_GAMEPLAY_TAG(VALUE_ARMOR, "Value.Armor");
UE_DEFINE_GAMEPLAY_TAG(VALUE_MAX_ARMOR, "Value.MaxArmor");
UE_DEFINE_GAMEPLAY_TAG(VALUE_SPEED, "Value.Speed");
UE_DEFINE_GAMEPLAY_TAG(VALUE_DEFAULT_SPEED, "Value.DefaultSpeed");
UE_DEFINE_GAMEPLAY_TAG(VALUE_POWER_DAMAGE, "Value.Damage");

void UEEC_SetDefaultValues::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                   FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	
	const UAbilitySystemComponent* TargetAsc = ExecutionParams.GetSourceAbilitySystemComponent();
	if (!TargetAsc)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target is nullptr! "));
		return;
	}

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	
	if (TargetAsc->GetSet<UAS_VitalAttributeSet>())
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UAS_VitalAttributeSet::GetHealthAttribute(), EGameplayModOp::Override,
			Spec.GetSetByCallerMagnitude(VALUE_HEALTH,true, 0)));
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UAS_VitalAttributeSet::GetMaxHealthAttribute(), EGameplayModOp::Override,
			Spec.GetSetByCallerMagnitude(VALUE_MAX_HEALTH,true, 0)));
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UAS_VitalAttributeSet::GetArmorAttribute(), EGameplayModOp::Override,
			Spec.GetSetByCallerMagnitude(VALUE_ARMOR,true, 0)));
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UAS_VitalAttributeSet::GetMaxArmorAttribute(), EGameplayModOp::Override,
			Spec.GetSetByCallerMagnitude(VALUE_MAX_ARMOR,true, 0)));
	}

	if (TargetAsc->GetSet<UAS_MovementAttributeSet>())
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UAS_MovementAttributeSet::GetCurrentSpeedAttribute(), EGameplayModOp::Override,
			Spec.GetSetByCallerMagnitude(VALUE_SPEED,true, 0)));
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UAS_MovementAttributeSet::GetDefaultSpeedAttribute(), EGameplayModOp::Override,
			Spec.GetSetByCallerMagnitude(VALUE_DEFAULT_SPEED,true, 0)));
	}

	if (TargetAsc->GetSet<UAS_DamageAttributeSet>())
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UAS_DamageAttributeSet::GetPowerDamageAttribute(), EGameplayModOp::Override,
			Spec.GetSetByCallerMagnitude(VALUE_POWER_DAMAGE,true, 0)));
	}
	
}