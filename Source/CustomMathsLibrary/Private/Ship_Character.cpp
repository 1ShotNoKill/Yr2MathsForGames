// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship_Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AShip_Character::AShip_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USkeletalMeshComponent* SkelMesh = GetMesh();
	USkeletalMesh* LoadedMesh = LoadObject<USkeletalMesh>(nullptr, TEXT(""));
		SkelMesh->SetSkeletalMesh(LoadedMesh);

	ShipMappingContext = LoadObject<UInputMappingContext>(nullptr, TEXT("/Game/Player/Inputs/PlayerContext_IMC.PlayerContext_IMC"));
}

// Called when the game starts or when spawned
void AShip_Character::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		//check if localplayer is using enhanced input subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(ShipMappingContext, 0);
	}
}

// Called every frame
void AShip_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShip_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Applies PlayerMappingContext to player subsystem
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		//check if localplayer is using enhanced input subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(ShipMappingContext, 0);
	}
	//Dynamically fills array with bound action names from IMC
	for (const FEnhancedActionKeyMapping& Mapping : ShipMappingContext->GetMappings())
	{
		if (Mapping.Action)
		{
			FName Name = Mapping.Action->GetFName();
			const UInputAction* Action = Mapping.Action.Get();
			InputActions.Add(Name, Action);
		}

		//if context contains any of these actions then bind to functions
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
		{
			/*if (InputActions.Contains("Teleport_IA")) EnhancedInputComponent->BindAction(InputActions["Teleport_IA"], ETriggerEvent::Triggered, this, &AMyPlayer::TeleportPlayer);
			if (InputActions.Contains("Move_IA")) EnhancedInputComponent->BindAction(InputActions["Move_IA"], ETriggerEvent::Triggered, this, &AMyPlayer::Move);*/
		}
	}


}

