// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPProject/TPAttributeSet.h"
#include "AS_WeaponAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TPPROJECT_API UAS_WeaponAttributeSet : public UTPAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Ammo;
	ATTRIBUTE_ACCESSORS(UAS_WeaponAttributeSet, Ammo);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxAmmo;
	ATTRIBUTE_ACCESSORS(UAS_WeaponAttributeSet, MaxAmmo);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData WeaponDamage;
	ATTRIBUTE_ACCESSORS(UAS_WeaponAttributeSet, WeaponDamage);
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
};
