// Fill out your copyright notice in the Description page of Project Settings.


#include "TPProject/GameplayExecutionCalcution/EEC_DamageCalculate.h"

#include "AbilitySystemComponent.h"
#include "TPProject/GameplayerAttributes/AS_VitalAttributeSet.h"

void UEEC_DamageCalculate::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                  FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	
	const UAbilitySystemComponent* TargetAsc = ExecutionParams.GetTargetAbilitySystemComponent();
	    
	// Перевіряємо, чи є у цілі тег State.Invinsible
	if (TargetAsc->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Status.Invinsibility"))))
	{
		// Ціль невразлива — не застосовуємо пошкодження
		return;
	}
	
	//Доступ до атрибутів
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	if (!TargetAsc)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target is nullptr! "));
		return;
	}	
	
	//Значення броні та здоров'я
	float ArmorValue = TargetAsc->GetNumericAttribute(UAS_VitalAttributeSet::GetArmorAttribute());
	float HealthValue = TargetAsc->GetNumericAttribute(UAS_VitalAttributeSet::GetHealthAttribute());

	//Початкове пошкодження з ефекту
	float Damage = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Effect.Damage")), true, 5);
	
	//Розрахунок віднімання броні
	float DamageToArmor = FMath::Min(Damage, ArmorValue);
	ArmorValue -= DamageToArmor;
	Damage -= DamageToArmor;

	//Залишок пошкодження для віднімання здоров'я
	if(Damage > 0.f)
	{
		HealthValue -= Damage;
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UAS_VitalAttributeSet::GetHealthAttribute(), EGameplayModOp::Override, HealthValue));
	}
	
	//Оновлення значення броні та здоров'я
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UAS_VitalAttributeSet::GetArmorAttribute(), EGameplayModOp::Override, ArmorValue));
}