// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "TPAttributeSet.h"
#include "TestAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TPPROJECT_API UTestAttributeSet : public UTPAttributeSet
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData TestAttribute;
	ATTRIBUTE_ACCESSORS(UTestAttributeSet, TestAttribute);
};
