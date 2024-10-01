// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPAttributeSet.h"
#include "AS_MovementAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TPPROJECT_API UAS_MovementAttributeSet : public UTPAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UAS_MovementAttributeSet, Speed);
};
