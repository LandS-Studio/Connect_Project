// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "NativeGameplayTags.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayTagContainer.h"
#include "Components/WidgetComponent.h"
#include "Logging/LogMacros.h"
#include "TPProjectCharacter.generated.h"


UE_DECLARE_GAMEPLAY_TAG_EXTERN(STATUS_DEAD);

class USpringArmComponent;
//class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ATPProjectCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	/* Camera boom positioning the camera behind the character 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	*/
	
	/* Follow camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	*/
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** JumpInput Action */
	/*
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	*/
		
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;


public:
	ATPProjectCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TMap<FGameplayTag, float> DefaultSettings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float MoveX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float MoveY;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void RotateCharacterToPoint(const FVector& HitLocation);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Status")
	void OnStatusChanged(bool bActivation, FGameplayTag StatusTag);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Status")
	void OnSetPlayerDeath(bool bIsDead);

	UFUNCTION(BlueprintCallable, Category = "Status")
	bool GetIsAlive();

	UFUNCTION(BlueprintCallable, Category = "GameplayEffect")
	float GetActiveEffectDuration(FActiveGameplayEffectHandle EffectHandle);

	/** Returns CameraBoom subobject 
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	*/
	/** Returns FollowCamera subobject 
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	*/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

protected:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Cursor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* PreviewPlacing;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* PlayerInfo;
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();
	
};

