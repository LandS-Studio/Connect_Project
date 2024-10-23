// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPProject/TPAttributeSet.h"
#include "AS_InventoryAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TPPROJECT_API UAS_InventoryAttributeSet : public UTPAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData HandgunAmmo;
	ATTRIBUTE_ACCESSORS(UAS_InventoryAttributeSet, HandgunAmmo);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData AssaultAmmo;
	ATTRIBUTE_ACCESSORS(UAS_InventoryAttributeSet, AssaultAmmo);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData HuntingAmmo;
	ATTRIBUTE_ACCESSORS(UAS_InventoryAttributeSet, HuntingAmmo);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData ShotgunAmmo;
	ATTRIBUTE_ACCESSORS(UAS_InventoryAttributeSet, ShotgunAmmo);
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData SniperAmmo;
	ATTRIBUTE_ACCESSORS(UAS_InventoryAttributeSet, SniperAmmo);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MiniGunAmmo;
	ATTRIBUTE_ACCESSORS(UAS_InventoryAttributeSet, MiniGunAmmo);
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
};
