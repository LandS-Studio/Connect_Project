// Fill out your copyright notice in the Description page of Project Settings.


#include "AS_MovementAttributeSet.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TPProject/TPProjectCharacter.h"

void UAS_MovementAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	//Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if(Attribute == GetCurrentSpeedAttribute())
	{
		if(UAbilitySystemComponent* TargetASC = GetOwningAbilitySystemComponent())
		{
			if(ATPProjectCharacter* OwnerActor = Cast<ATPProjectCharacter>(TargetASC->GetAvatarActor()))
			{
				if(UCharacterMovementComponent* MovementComponent = OwnerActor->GetCharacterMovement())
				{
					MovementComponent->MaxWalkSpeed = NewValue;
					if(NewValue > DefaultSpeed.GetCurrentValue())
					{
						TargetASC->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Status.SpeedDown")));
						OwnerActor->OnStatusChanged(false, FGameplayTag::RequestGameplayTag(FName("Status.SpeedDown")));
						TargetASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Status.SpeedUp")));
						OwnerActor->OnStatusChanged(true, FGameplayTag::RequestGameplayTag(FName("Status.SpeedUp")));
					} else if (NewValue < DefaultSpeed.GetCurrentValue())
					{
						TargetASC->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Status.SpeedUp")));
						OwnerActor->OnStatusChanged(false, FGameplayTag::RequestGameplayTag(FName("Status.SpeedUp")));
						TargetASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Status.SpeedDown")));
						OwnerActor->OnStatusChanged(true, FGameplayTag::RequestGameplayTag(FName("Status.SpeedDown")));
					} else if (NewValue == DefaultSpeed.GetCurrentValue())
					{
						TargetASC->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Status.SpeedDown")));
						OwnerActor->OnStatusChanged(false, FGameplayTag::RequestGameplayTag(FName("Status.SpeedDown")));
						TargetASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Status.SpeedUp")));
						OwnerActor->OnStatusChanged(false, FGameplayTag::RequestGameplayTag(FName("Status.SpeedUp")));
					}					
				}
			}
		}
	}
}
