// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship_Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"



// Sets default values
AShip_Character::AShip_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetDefaults();
}

void AShip_Character::SetDefaults() 
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		StaticMeshComponent->SetRelativeRotation(FRotator(0, 90, 0));
		if(RootComponent) StaticMeshComponent->SetupAttachment(RootComponent);
		
		UStaticMesh* LoadedMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Models/Boat.Boat"));
			if (LoadedMesh) StaticMeshComponent->SetStaticMesh(LoadedMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
		if (RootComponent) SpringArm->SetupAttachment(StaticMeshComponent);
		SpringArm->SetRelativeRotation(FRotator(0, -90, 0));
		SpringArm->TargetArmLength = 200.f;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		Camera->SetupAttachment(SpringArm);

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

	ShipController = GetController<AShipController>();
}

void AShip_Character::Look(const FInputActionValue& Value)
{
	FVector2D Vector2D = Value.Get<FVector2D>();
	FMyVector2 ConvertedVector2D = FMyVector2(Vector2D.X, Vector2D.Y);
	ShipController->Look(ConvertedVector2D);

	FRotator Newrot = FRotator(ShipController->pitchDeg, ShipController->yawDeg,0.f);

	SetActorRotation(Newrot);

	
}

void AShip_Character::Move(const FInputActionValue& Value)
{
	FVector2D Vector2D = Value.Get<FVector2D>();
	FMyVector2 ConvertedVector2D = FMyVector2(Vector2D.X, Vector2D.Y);
	ShipController->Move(ConvertedVector2D);

	AddActorWorldOffset(MyMathLibrary::ConvertFromCustomVector(ShipController->StepMovement), true);
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
			if (InputActions.Contains("Look_IA")) EnhancedInputComponent->BindAction(InputActions["Look_IA"], ETriggerEvent::Triggered, this, &AShip_Character::Look);
			if (InputActions.Contains("Move_IA")) EnhancedInputComponent->BindAction(InputActions["Move_IA"], ETriggerEvent::Triggered, this, &AShip_Character::Move);
		}
	}


}

