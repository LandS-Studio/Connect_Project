// Fill out your copyright notice in the Description page of Project Settings.


#include "AS_VitalAttributeSet.h"
#include "TPProject/TPProjectCharacter.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(STATUS_DEAD);

void UAS_VitalAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if(Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, MaxHealth.GetCurrentValue());
	}

	if(Attribute == GetArmorAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, MaxArmor.GetCurrentValue());
	}
	
	
}

void UAS_VitalAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	UAbilitySystemComponent* TargetASC = GetOwningAbilitySystemComponent();
		
	if(Attribute == GetHealthAttribute())
	{
		ATPProjectCharacter* OwnerCharacter = Cast<ATPProjectCharacter>(TargetASC->GetAvatarActor());
		
		if(OwnerCharacter && NewValue <= 0.0f)
		{
			if(TargetASC)
			{
				TargetASC->AddLooseGameplayTag(STATUS_DEAD);
				OwnerCharacter->OnSetPlayerDeath(true);
			}
		} 
	}
}
