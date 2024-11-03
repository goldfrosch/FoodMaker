#include "FoodMakerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "Engine/OverlapResult.h"
#include "FoodMaker/Assets/Machine/DefaultMachine.h"
#include "FoodMaker/Assets/Item/ItemableActor.h"
#include "FoodMaker/Player/BasePlayerController.h"
#include "FoodMaker/Player/BasePlayerState.h"
#include "FoodMaker/Widgets/InventoryUI.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);


AFoodMakerCharacter::AFoodMakerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AFoodMakerCharacter::BeginPlay()
{
	Super::BeginPlay();
	InteractionObject();
	FindDroppedItems();
	
	if (!InventoryUI)
	{
		InventoryUI = CreateWidget<UInventoryUI>(Cast<APlayerController>(GetController()), InventoryUIClass);
	}
}

void AFoodMakerCharacter::FindDroppedItems()
{
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(150);
	
	TArray<FOverlapResult> OverlapItemResults;
	
	if (GetWorld()->OverlapMultiByChannel(
		OverlapItemResults,
		GetActorLocation(),
		FQuat::Identity,
		ECC_Visibility,
		CollisionShape
	))
	{
		if (ABasePlayerState* PS = Cast<ABasePlayerState>(GetPlayerState()))
		{
			for (FOverlapResult& OverlapItemResult : OverlapItemResults)
			{
				if (AItemableActor* ItemableActor = Cast<AItemableActor>(OverlapItemResult.GetActor()))
				{
					UE_LOG(LogTemp, Display, TEXT("하이하이요"))
					FInventoryData NewItem;
                	NewItem.ItemInfo = ItemableActor->GetClass();
                	NewItem.Count = 1;
					
					PS->InventoryDataList.Add(NewItem);
				}
			}
		}
	}}


void AFoodMakerCharacter::InteractionObject()
{
	FHitResult HitResult;
	TArray<AActor*> ActorsToNotTargeting;
	FVector Start = GetCameraBoom()->GetComponentLocation();
	FVector End = Start + GetCameraBoom()->GetForwardVector() * 500;
	
	if (GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(8.f)))
	{
		if (ADefaultMachine* Machine = Cast<ADefaultMachine>(HitResult.GetActor()))
		{
			// TODO: 화면에 보일 시 interaction UI 노출
			if (ABasePlayerController* PC = Cast<ABasePlayerController>(GetController()))
			{
				PC->SetSelectedInteractiveMachine(Machine);
			}
		}
	} else
    {
     	if (ABasePlayerController* PC = Cast<ABasePlayerController>(GetController()))
     	{
     		PC->SetSelectedInteractiveMachine(nullptr);
     	}
    }
}



void AFoodMakerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFoodMakerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFoodMakerCharacter::Look);
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Triggered, this, &AFoodMakerCharacter::OpenInventory);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AFoodMakerCharacter::OpenInventory(const FInputActionValue& Value)
{
	if (InventoryUI->IsVisible())
	{
		InventoryUI->RemoveFromParent();
	} else
	{
		InventoryUI->AddToViewport();
	}
}


void AFoodMakerCharacter::Move(const FInputActionValue& Value)
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
		
		InteractionObject();
		FindDroppedItems();
	}
}

void AFoodMakerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}