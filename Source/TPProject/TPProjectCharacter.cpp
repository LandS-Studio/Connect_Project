// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPProjectCharacter.h"

#include "AbilitySystemComponent.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "TPPlayerState.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"

UE_DEFINE_GAMEPLAY_TAG(STATUS_DEAD, "Status.Dead");

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATPProjectCharacter

ATPProjectCharacter::ATPProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	
	Cursor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerCursor"));
	Cursor->SetupAttachment(RootComponent);
	Cursor->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	PreviewPlacing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewPlacing"));
	PreviewPlacing->SetupAttachment(RootComponent);
	
	PlayerInfo = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerInfo"));
	PlayerInfo->SetupAttachment(RootComponent);

	ArrowDropLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowDropLocation"));
	ArrowDropLocation->SetupAttachment(RootComponent);

	/*
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	*/
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ATPProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void ATPProjectCharacter::RotateCharacterToPoint(const FVector& HitLocation)
{
	if(Controller != nullptr)
	{
		const FRotator NewRotation = FMath::RInterpTo(	GetActorRotation(),
														UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),
														HitLocation),GetWorld()->GetTimeSeconds(),10.f);
		
		SetActorRotation(FRotator(0.0f, NewRotation.Yaw , 0.0f));
	}
}

bool ATPProjectCharacter::GetIsAlive()
{
	if(GetAbilitySystemComponent())
	{
		FGameplayTagContainer OwnedTags;

		GetAbilitySystemComponent()->GetOwnedGameplayTags(OwnedTags);

		if(OwnedTags.HasTag(STATUS_DEAD))
		{
			return false;
		}
		
		return true;
		
	}
	return true;
}

float ATPProjectCharacter::GetActiveEffectDuration(FActiveGameplayEffectHandle EffectHandle)
{
	
	if(GetAbilitySystemComponent())
	{
		if (const FActiveGameplayEffect* ActiveEffect = GetAbilitySystemComponent()->GetActiveGameplayEffect(EffectHandle))
		{
			return ActiveEffect->GetDuration();
		}
	}
	
	return 0.0f;
}

UAbilitySystemComponent* ATPProjectCharacter::GetAbilitySystemComponent() const
{
	if (const ATPPlayerState* TPPlayerState = GetPlayerState<ATPPlayerState>())
	{
		return TPPlayerState->GetAbilitySystemComponent();
	}
	return nullptr;
}

void ATPProjectCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (const ATPPlayerState* TPPlayerState = GetPlayerState<ATPPlayerState>())
	{
		return TPPlayerState->GetAbilitySystemComponent()->SetAvatarActor(this);
	}
}

void ATPProjectCharacter::UnPossessed()
{
	Super::UnPossessed();
	if (const ATPPlayerState* TPPlayerState = GetPlayerState<ATPPlayerState>())
	{
		return TPPlayerState->GetAbilitySystemComponent()->SetAvatarActor(nullptr);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATPProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATPProjectCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATPProjectCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

void ATPProjectCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}


void ATPProjectCharacter::Look(const FInputActionValue& Value)
{	
	if (Controller != nullptr)
	{
		if(Cursor)
		{
			FVector HitLocation = Cursor->GetComponentLocation();
			HitLocation.Z += 2;
			RotateCharacterToPoint(HitLocation);
		}
	}
}


