// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPProject/TPAttributeSet.h"
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
	FGameplayAttributeData CurrentSpeed;
	ATTRIBUTE_ACCESSORS(UAS_MovementAttributeSet, CurrentSpeed);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData DefaultSpeed;
	ATTRIBUTE_ACCESSORS(UAS_MovementAttributeSet, DefaultSpeed);

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
};
