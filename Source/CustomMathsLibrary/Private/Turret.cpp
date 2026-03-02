// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Kismet/GameplayStatics.h"




// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LocalOffset = FMyVector3(0, 40, 5);

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	if(RootComponent) RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	if(Root) Mesh->SetupAttachment(Root);
	Mesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr,TEXT("/Game/Models/Turret.Turret")));
	Mesh->SetRelativeRotation(FRotator(0, 180, 0));
	Mesh->SetRelativeLocation(FVector(0, 0, 0));
	Mesh->SetWorldScale3D(FVector(0.5, 0.5, 0.5));

	Mesh->SetCollisionProfileName(FName(TEXT("NoCollision")));
	
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShip_Character::StaticClass(), FoundActors);

	PlayerShip = Cast<AShip_Character>(FoundActors[0]);
	ShipController = PlayerShip->CustomGetController();

	if(PlayerShip)PlayerShip->OnShot.AddDynamic(this, &ATurret::TurretShoot);

}

void ATurret::TurretShoot(const FInputActionValue& Value)
{
		UE_LOG(LogTemp,Warning,TEXT("Fire Turret"));
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerShip && ShipController)
	{
		FMyVector3 R = ShipController->RightVector;
		FMyVector3 U = ShipController->UpVector;
		FMyVector3 F = ShipController->ForwardVector;

		FMyVector3 P = MyMathLibrary::ConvertToCustomVector(PlayerShip->GetActorLocation());

		FMyVector3 DFB = MyMathLibrary::DirectionFromBasis(LocalOffset, R, U, F);

		SetActorLocation(MyMathLibrary::ConvertFromCustomVector(MyMathLibrary::LocalPointToWorldPoint(P, LocalOffset, R, U, F)));
		
		
		
		
		FRotator PlayerRotation = PlayerShip->GetActorRotation();
		FRotator TargetRotation = FRotator(PlayerRotation.Pitch, PlayerShip->Camera->GetComponentRotation().Yaw, PlayerRotation.Roll);

		float OffsetRotationSpeed = BaseTurretRotationSpeed;

		FRotator RotStep = MyMathLibrary::LinearRotatorLerp(GetActorRotation(), TargetRotation, OffsetRotationSpeed, GetWorld()->DeltaRealTimeSeconds);

		SetActorRotation(RotStep);

		
	}
}

