// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPProject/TPAttributeSet.h"
#include "AS_DamageAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TPPROJECT_API UAS_DamageAttributeSet : public UTPAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData CurrentDamage;
	ATTRIBUTE_ACCESSORS(UAS_DamageAttributeSet, CurrentDamage);
};
