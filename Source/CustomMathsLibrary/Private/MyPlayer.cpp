// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "MyMathLibrary.h"
#include "Kismet/GameplayStatics.h"
//Movement system
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <TestActor.h>

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpawnCamera();

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> Context(TEXT("/Game/Player/Inputs/PlayerContext_IMC.PlayerContext_IMC"));
	if (Context.Succeeded())
	{
		PlayerMappingContext = Context.Object;
	}
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();


	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		//check if localplayer is using enhanced input subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
	}
}

void AMyPlayer::SpawnCamera()
{

}

void AMyPlayer::TeleportPlayer()
{

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ATestActor::StaticClass(), FoundActors);

	if (FoundActors[0])
	{
		float ActorX = FoundActors[0]->GetActorLocation().X;
		float ActorY = FoundActors[0]->GetActorLocation().Y;
		FMyVector2 ActorVector(ActorX, ActorY);

		float PlayerX = GetActorLocation().X;
		float PlayerY = GetActorLocation().Y;
		FMyVector2 PlayerVector(PlayerX, PlayerY);

		float Dist = MyMathLibrary::Distance2D(PlayerVector, ActorVector);
		UE_LOG(LogTemp, Warning, TEXT("Dist = %f"), Dist);
		if (Dist < 500.f)
		{
			SetActorLocation(FVector(ActorVector.x, ActorVector.y, 0.f));
			UE_LOG(LogTemp, Warning, TEXT("Player Teleported"));
		}


	}





}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AMyPlayer::Move(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		//Get 2D vector, X = forward & Backwards, Y = Right & Left
		FVector2D MovementVector = Value.Get<FVector2D>();

		//Get Forward & Right Direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		//Adding movement Forward or Right
		AddMovementInput(ForwardDir, MovementVector.X);
		AddMovementInput(RightDir, MovementVector.Y);
	}
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Applies PlayerMappingContext to player subsystem
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		//check if localplayer is using enhanced input subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
	}
	//Dynamically fills array with bound action names from IMC
	for (const FEnhancedActionKeyMapping& Mapping : PlayerMappingContext->GetMappings())
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
			if (InputActions.Contains("Teleport_IA")) EnhancedInputComponent->BindAction(InputActions["Teleport_IA"], ETriggerEvent::Triggered, this, &AMyPlayer::TeleportPlayer);
			if (InputActions.Contains("Move_IA")) EnhancedInputComponent->BindAction(InputActions["Move_IA"], ETriggerEvent::Triggered, this, &AMyPlayer::Move);
		}
	}
}

