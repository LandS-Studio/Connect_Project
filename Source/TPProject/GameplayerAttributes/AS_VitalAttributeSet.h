// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPProject/TPAttributeSet.h"
#include "AS_VitalAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TPPROJECT_API UAS_VitalAttributeSet : public UTPAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAS_VitalAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAS_VitalAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAS_VitalAttributeSet, Armor);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxArmor;
	ATTRIBUTE_ACCESSORS(UAS_VitalAttributeSet, MaxArmor);
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
};
