// Fill out your copyright notice in the Description page of Project Settings.



#include "Ship_Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Turret.h"
#include "SmallTurret.h"
#include "PickupActor.h"

// Sets default values
AShip_Character::AShip_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	SetDefaults();
}

void AShip_Character::SetDefaults() 
{
	/*Ship Mesh*/
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		StaticMeshComponent->SetRelativeRotation(FRotator(0, 90, 0));
		StaticMeshComponent->SetRelativeLocation(FVector(0, 0, -10));
		if(RootComponent) StaticMeshComponent->SetupAttachment(RootComponent);
		
		UStaticMesh* LoadedMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Models/Boat.Boat"));
			if (LoadedMesh) StaticMeshComponent->SetStaticMesh(LoadedMesh);
	/*CameraSpringArm*/
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
		if (RootComponent) SpringArm->SetupAttachment(StaticMeshComponent);
		SpringArm->SetRelativeLocation(FVector(0, 0, 92.563689));
		SpringArm->SetRelativeRotation(FRotator(-20, -90, 0));
		SpringArm->TargetArmLength = 200.f;

	/*Camera*/
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		Camera->SetupAttachment(SpringArm);
		SpringArm->bDoCollisionTest = false;

	/*Load PlayerInputContext*/
	ShipMappingContext = LoadObject<UInputMappingContext>(nullptr, TEXT("/Game/Player/Inputs/PlayerContext_IMC.PlayerContext_IMC"));
}

AShipController* AShip_Character::CustomGetController()
{
	return Cast<AShipController>(GetController());
}

// Called when the game starts or when spawned
void AShip_Character::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
	}

	ShipController = GetController<AShipController>();

	/*Spawn Main Turret in world*/
	ATurret* MainTurret = GetWorld()->SpawnActor<ATurret>(ATurret::StaticClass(), GetActorTransform());
		MainTurret->SetShipCharacterReference(this);
		MainTurret->LocalOffset = FMyVector3(0, 40, 0);

		if (ShipTurrets.Contains(ETurretType::MainTurret))
		{
			ShipTurrets[ETurretType::MainTurret].Add(MainTurret);
			UE_LOG(LogTemp, Warning, TEXT("Added MainTurret To Array"));
			UE_LOG(LogTemp, Warning, TEXT("Added Turret, if"));
		}
		else
		{
			ShipTurrets.Add(ETurretType::MainTurret);
			ShipTurrets[ETurretType::MainTurret].Add(MainTurret);
			UE_LOG(LogTemp, Warning, TEXT("Added Turret, else"));
		}
		
	/*Spawns GunTurret in world*/
	ATurret* GunTurret = GetWorld()->SpawnActor<ASmallTurret>(ASmallTurret::StaticClass(), GetActorTransform());
		GunTurret->SetShipCharacterReference(this);
		GunTurret->LocalOffset = FMyVector3(0, 40, 40);
		if (ShipTurrets.Contains(ETurretType::GunTurret))
		{
			ShipTurrets[ETurretType::GunTurret].Add(GunTurret);
			UE_LOG(LogTemp, Warning, TEXT("Added GunTurret To Array"));
			UE_LOG(LogTemp, Warning, TEXT("Added Turret, if"));
		}
		else
		{
			ShipTurrets.Add(ETurretType::GunTurret);
			ShipTurrets[ETurretType::GunTurret].Add(GunTurret);
			UE_LOG(LogTemp, Warning, TEXT("Added Turret,else"));
		}

	//CreateCustomBoundingBox
		BoundingBox Newbox(this, FMyVector3(100.f, 60.f, 75.f),FMyVector3(0,0,35),-1);
		CollisionBox = Newbox;

		PickupActor = Cast<APickupActor>(UGameplayStatics::GetActorOfClass(GetWorld(), APickupActor::StaticClass()));
		

		

		
}

void AShip_Character::Look(const FInputActionValue& Value)
{
	FVector2D Vector2D = Value.Get<FVector2D>();
	FMyVector2 ConvertedVector2D = FMyVector2(Vector2D.X, Vector2D.Y);
	ShipController->Look(ConvertedVector2D);

	FRotator Newrot = FRotator(ShipController->pitchDeg, ShipController->yawDeg,0.f);
	SpringArm->SetRelativeRotation(Newrot);
}

void AShip_Character::Move(const FInputActionValue& Value)
{
	

	FVector2D Vector2D = Value.Get<FVector2D>();
	FMyVector2 ConvertedVector2D = FMyVector2(Vector2D.X, Vector2D.Y);



	/*Calculates Radians from Ship Rotation*/
	float YawRadians = MyMathLibrary::DegreesToRadians(GetActorRotation().Yaw);
	float PitchRadians = MyMathLibrary::DegreesToRadians(GetActorRotation().Pitch);

	FMyVector3 UpVector = FMyVector3(0, 0, 1); //X,Y,Z
	ShipController->UpVector = UpVector;

	/*Calculate Forward Vector using Yaw & Pitch Radians*/
	FMyVector3 ForwardVector = MyMathLibrary::ForwardFromYawPitch(YawRadians, PitchRadians);
			   ForwardVector.z = 0;
			   ForwardVector = MyMathLibrary::Normalize(ForwardVector);
			   ShipController->ForwardVector = ForwardVector;

	/*Calaculate Right vector using Up & Forward*/
	FMyVector3 RightVector = (MyMathLibrary::CrossProduct(FMyVector3(UpVector), ForwardVector));
			   RightVector = MyMathLibrary::Normalize(RightVector);
			   ShipController->RightVector = RightVector;

			   if (BCanMoveForward == false && Vector2D.X > 0)
			   {
				   Vector2D.X = 0;
			   }
			   FMyVector3 ScaledForward = MyMathLibrary::Scale(ForwardVector, Vector2D.X);


	/*Calculate the New Position using Scaled Forward Vector & ShipSpeed, multiplied by DeltaTime to ensure smooth motion*/
			  
	FMyVector3 MoveStep = MyMathLibrary::MoveStep(ScaledForward, ShipSpeed, GetWorld()->DeltaRealTimeSeconds);


	FMyVector3 Location = MyMathLibrary::ConvertToCustomVector(RootComponent->GetComponentLocation());
	Location = MyMathLibrary::Add3D(Location, MoveStep);

	RootComponent->SetWorldLocation(MyMathLibrary::ConvertFromCustomVector(Location));

	/*Yaw Rotation*/
	float DeltaYaw = RotationSpeed * Vector2D.Y * GetWorld()->DeltaRealTimeSeconds;

	FRotator DeltaRotation = FRotator(0, DeltaYaw, 0);
	FRotator NewRotation = MyMathLibrary::AddRotation(GetActorRotation(), DeltaRotation);

	RootComponent->SetWorldRotation(NewRotation);
}

void AShip_Character::SelectTurret(const FInputActionValue& Value)
{
	if (!bCanSwitch) return;
	bCanSwitch = false;

	float Selected = Value.Get<float>();
	int SelectedINT = FMath::RoundToInt(Selected);
	UE_LOG(LogTemp, Warning, TEXT("%d"), SelectedINT);
	ETurretType NewSelection = static_cast<ETurretType>(SelectedINT);
	if (NewSelection == SelectedTurretType)
	{
		NewSelection = static_cast<ETurretType>(0);
	}
	SelectedTurretType = NewSelection;

	GetWorldTimerManager().SetTimerForNextTick([this]()
		{
			bCanSwitch = true;
		});
}

//shoots turrets based on selected turret type
void AShip_Character::Shoot()
{
	TArray<ATurret*> SelectedTurrets;
	if (SelectedTurretType == ETurretType::AllTurrets) //Selects all turrets within ShipTurret map
	{
		for (const auto& Pair : ShipTurrets)
		{
			for (ATurret* Turret : Pair.Value)
			{
				SelectedTurrets.Add(Turret);
			}
		}
	}
	else SelectedTurrets = ShipTurrets[SelectedTurretType]; //select all turrets of a type within ShipTurret Map

	for (ATurret* Turret : SelectedTurrets)
	{
		if(Turret) Turret->TurretShoot();
		//UE_LOG(LogTemp, Warning, TEXT("Fired"));
	}
}

// Called every frame
void AShip_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShipEnemy::StaticClass(), Enemies);


	float Distance = 999999.f;
	AActor* ClosestEnemy = nullptr;
	FMyVector3 PlayerPos = MyMathLibrary::ConvertToCustomVector(GetActorLocation());

	//Loops through all enemies to determine closest by distance
	for (AActor* Enemy : Enemies)
	{
		FMyVector3 EnemyPos = MyMathLibrary::ConvertToCustomVector(Enemy->GetActorLocation());

		if (float DistTemp = MyMathLibrary::Distance3D(EnemyPos, PlayerPos) < Distance)
		{
			Distance = DistTemp;
			ClosestEnemy = Enemy;
		}
		
	}
	
	//after determining closest, cast to that actor to access collisionbox variable
	if (ClosestEnemy)
	{
		NearestEnemy = Cast<AShipEnemy>(ClosestEnemy);

		//Do AABB collision test on closest enemy
		FMyVector3 EnemyOverlap = CollisionBox.AABBOverlap(NearestEnemy->CollisionBox);
		if (EnemyOverlap.x > 0 && EnemyOverlap.y > 0 && EnemyOverlap.z > 0)
		{
			BCanMoveForward = false; //if colliding with enemy stop ship
		}
		else if (BCanMoveForward == false)
		{
			BCanMoveForward = true; // else allow movement
		}

	}
	

	
	CollisionBox.DebugDrawBox();

		//Collision Detection for powerup
		if (PickupActor && PickupActor->BCollisionEnabled == true)
		{
		 FMyVector3 Overlap = CollisionBox.AABBOverlap(PickupActor->CollisionBox);
		 if (Overlap.x > 0 && Overlap.y >0 && Overlap.z > 0)
		 {
			 UE_LOG(LogTemp, Warning, TEXT("Overlapped"));
			 PickupActor->BCollisionEnabled = false;
			 PowerUp = PickupActor; 
		 }
		}
		if (PowerUp)
		{
			MyMathLibrary::RotateObjectAroundParent(this, PowerUp, FMyVector3(100, 0, 75), FMyVector3(0, 0, 1), 85.f, DeltaTime, CurrentDeg);
		}
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
			if (InputActions.Contains("Shoot_IA")) EnhancedInputComponent->BindAction(InputActions["Shoot_IA"], ETriggerEvent::Triggered, this, &AShip_Character::Shoot);
			if (InputActions.Contains("PrimaryTurretSelection_IA")) EnhancedInputComponent->BindAction(InputActions["PrimaryTurretSelection_IA"], ETriggerEvent::Started, this, &AShip_Character::SelectTurret);
			if (InputActions.Contains("SecondaryTurretSelection_IA")) EnhancedInputComponent->BindAction(InputActions["SecondaryTurretSelection_IA"], ETriggerEvent::Started, this, &AShip_Character::SelectTurret);

		}
	}
}
