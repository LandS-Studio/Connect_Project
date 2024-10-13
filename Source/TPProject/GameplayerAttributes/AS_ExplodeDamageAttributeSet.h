// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "NativeGameplayTags.h"
#include "CoreMinimal.h"
#include "TPProject/TPAttributeSet.h"
#include "AS_ExplodeDamageAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TPPROJECT_API UAS_ExplodeDamageAttributeSet : public UTPAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData ExplodeDamage;
	ATTRIBUTE_ACCESSORS(UAS_ExplodeDamageAttributeSet, ExplodeDamage);
};
