// Fill out your copyright notice in the Description page of Project Settings.


#include "EEC_SetDefaultWeaponValues.h"
#include "TPProject/GameplayerAttributes/AS_WeaponAttributeSet.h"

UE_DEFINE_GAMEPLAY_TAG(VALUE_AMMO, "Value.Ammo");
UE_DEFINE_GAMEPLAY_TAG(VALUE_MAX_AMMO, "Value.MaxAmmo");
UE_DEFINE_GAMEPLAY_TAG(VALUE_WEAPON_DAMAGE, "Value.WeaponDamage");

void UEEC_SetDefaultWeaponValues::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
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
	
	if (TargetAsc->GetSet<UAS_WeaponAttributeSet>())
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UAS_WeaponAttributeSet::GetAmmoAttribute(), EGameplayModOp::Override,
			Spec.GetSetByCallerMagnitude(VALUE_AMMO,true, 0)));
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UAS_WeaponAttributeSet::GetMaxAmmoAttribute(), EGameplayModOp::Override,
			Spec.GetSetByCallerMagnitude(VALUE_MAX_AMMO,true, 0)));
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UAS_WeaponAttributeSet::GetWeaponDamageAttribute(), EGameplayModOp::Override,
			Spec.GetSetByCallerMagnitude(VALUE_WEAPON_DAMAGE,true, 0)));
	}
}