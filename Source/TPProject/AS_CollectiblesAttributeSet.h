// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPAttributeSet.h"
#include "AS_CollectiblesAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TPPROJECT_API UAS_CollectiblesAttributeSet : public UTPAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Coins;
	ATTRIBUTE_ACCESSORS(UAS_CollectiblesAttributeSet, Coins);
};
