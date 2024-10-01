// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPAttributeSet.h"
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
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UAS_DamageAttributeSet, Damage);
};
