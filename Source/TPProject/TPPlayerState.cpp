// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPlayerState.h"
#include "AbilitySystemComponent.h"

ATPPlayerState::ATPPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
}
