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
		Mesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr,*TurretBase));
		Mesh->SetRelativeRotation(FRotator(0, 180, 0));
		Mesh->SetRelativeLocation(FVector(0, 0, 0));
		Mesh->SetWorldScale3D(FVector(0.5, 0.5, 0.5));
		Mesh->SetCollisionProfileName(FName(TEXT("NoCollision")));

	Barrel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretBarrel"));
	Barrel->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *TurretBarrel));
	Barrel->SetupAttachment(Mesh);
	Barrel->SetCollisionProfileName(FName(TEXT("NoCollision")));
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShip_Character::StaticClass(), FoundActors);

	PlayerShip = Cast<AShip_Character>(FoundActors[0]);
	ShipController = PlayerShip->CustomGetController();

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

		FMyVector3 P = MyMathLibrary::ConvertToCustomVector(PlayerShip->GetActorLocation()+ MyMathLibrary::ConvertFromCustomVector(PosOffset));

		FMyVector3 DFB = MyMathLibrary::DirectionFromBasis(LocalOffset, R, U, F);

		SetActorLocation(MyMathLibrary::ConvertFromCustomVector(MyMathLibrary::LocalPointToWorldPoint(P, LocalOffset, R, U, F)));
		
		
		
		
		FRotator PlayerRotation = PlayerShip->GetActorRotation();
		FRotator TargetRotation = FRotator(PlayerRotation.Pitch, PlayerShip->Camera->GetComponentRotation().Yaw, PlayerRotation.Roll);

		float OffsetRotationSpeed = BaseTurretRotationSpeed;

		FRotator RotStep = MyMathLibrary::LinearRotatorLerp(GetActorRotation(), TargetRotation, OffsetRotationSpeed, GetWorld()->DeltaRealTimeSeconds);
		SetActorRotation(RotStep);

		float BarrelPitch = PlayerShip->Camera->GetComponentRotation().Pitch;
		UE_LOG(LogTemp, Warning, TEXT("Before Clamp: %f"), BarrelPitch);
		BarrelPitch = MyMathLibrary::ClampInRange(BarrelPitch, -10, 40);
		UE_LOG(LogTemp, Warning, TEXT("After Clamp: %f"), BarrelPitch);
		FRotator BarrelRotation = FRotator(BarrelPitch*-1, Mesh->GetComponentRotation().Yaw, Mesh->GetComponentRotation().Roll);


		Barrel->SetWorldRotation(BarrelRotation, false);

		
	}
}

