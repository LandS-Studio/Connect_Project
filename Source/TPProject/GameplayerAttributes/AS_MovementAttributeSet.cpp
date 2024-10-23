// Fill out your copyright notice in the Description page of Project Settings.


#include "AS_MovementAttributeSet.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TPProject/TPProjectCharacter.h"


UE_DEFINE_GAMEPLAY_TAG(SPEED_DOWN, "Status.SpeedDown");
UE_DEFINE_GAMEPLAY_TAG(SPEED_UP, "Status.SpeedUp");

void UAS_MovementAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

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
						TargetASC->RemoveLooseGameplayTag(SPEED_DOWN);
						OwnerActor->OnStatusChanged(false, SPEED_DOWN);
						TargetASC->AddLooseGameplayTag(SPEED_UP);
						OwnerActor->OnStatusChanged(true, SPEED_UP);
					} else if (NewValue < DefaultSpeed.GetCurrentValue())
					{
						TargetASC->RemoveLooseGameplayTag(SPEED_UP);
						OwnerActor->OnStatusChanged(false, SPEED_UP);
						TargetASC->AddLooseGameplayTag(SPEED_DOWN);
						OwnerActor->OnStatusChanged(true, SPEED_DOWN);
					} else 
					{
						TargetASC->RemoveLooseGameplayTag(SPEED_DOWN);
						OwnerActor->OnStatusChanged(false, SPEED_DOWN);
						TargetASC->RemoveLooseGameplayTag(SPEED_UP);
						OwnerActor->OnStatusChanged(false, SPEED_UP);
					}					
				}
			}
		}
	}
}
