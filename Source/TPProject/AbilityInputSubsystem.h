// Copyright by GameDone Studio

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AbilityInputSubsystem.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class UAbilityInputSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UAbilityInputSubsystem();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetAbilityInputID(UInputAction* InputAction);

private:
	UFUNCTION()
	void InputTriggerAbility(int32 InputID);

	UFUNCTION()
	void InputCompletedAbility(int32 InputID);


private:
	UPROPERTY()
	TMap<UInputAction*, int32> InputMapping;

	int32 NextInputID = 1;
};
