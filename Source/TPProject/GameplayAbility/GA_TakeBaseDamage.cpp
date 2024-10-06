// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_TakeBaseDamage.h"

UGA_TakeBaseDamage::UGA_TakeBaseDamage()
{

}

void UGA_TakeBaseDamage::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{

}
void UGA_TakeBaseDamage::OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UGA_TakeBaseDamage::OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGA_TakeBaseDamage::EventReceived(FGameplayTag EventTag, FGameplayEventData EventData)
{
	
}