// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Kismet/GameplayStatics.h"
#include "Ship_Character.h"
#include "ShipController.h"
#include "TurretProjectile.h"



// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretBase = "/Game/Models/TurretBase.TurretBase";
	TurretBarrel = "/Game/Models/TurretBarrel.TurretBarrel";


	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	if(RootComponent) RootComponent = Root;

		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	if(Root) Mesh->SetupAttachment(Root);
		Mesh->SetRelativeRotation(FRotator(0, 0, 0));
		Mesh->SetRelativeLocation(FVector(0, 0, 0));
		Mesh->SetWorldScale3D(FVector(0.5, 0.5, 0.5));
		Mesh->SetCollisionProfileName(FName(TEXT("NoCollision")));

	Barrel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretBarrel"));
		Barrel->SetupAttachment(Mesh);
		Barrel->SetCollisionProfileName(FName(TEXT("NoCollision")));

}

void ATurret::SetShipCharacterReference(AShip_Character* OwningShip)
{
	if (OwningShip)
	{
		PlayerShip = OwningShip;
		ShipController = Cast<AShipController>(OwningShip->GetController());
	}	
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
}

void ATurret::OnConstruction(const FTransform& Transform)
{
	if (Mesh && !TurretBase.IsEmpty()) Mesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *TurretBase));
	if(Barrel && !TurretBarrel.IsEmpty()) Barrel->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *TurretBarrel));
}

void ATurret::ReloadTurret(float Time)
{
	bCanFire = false;

	FTimerHandle ReloadHandle;
	GetWorldTimerManager().SetTimer(ReloadHandle, [this]() {bCanFire = true;}, Time, false);
}

void ATurret::SpawnProjectile()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ATurretProjectile* Projectile = GetWorld()->SpawnActor<ATurretProjectile>(ATurretProjectile::StaticClass(),Barrel->GetComponentLocation() + Barrel->GetForwardVector() * 100, Barrel->GetComponentRotation(), SpawnParams);

	if (Projectile)
	{

		FRotator BarrelRot = Barrel->GetComponentRotation();

		float Yaw = BarrelRot.Yaw;
		float Pitch = BarrelRot.Pitch;
		
		float YawRad = MyMathLibrary::DegreesToRadians(Yaw);
		float PitchRad = MyMathLibrary::DegreesToRadians(Pitch);

		//World up
		FMyVector3 UpVector = FMyVector3(0, 0, 1);

		//Calculate Forward from yaw & pitch 
		FMyVector3 ForwardVector = MyMathLibrary::ForwardFromYawPitch(YawRad, PitchRad);
		ForwardVector = MyMathLibrary::Normalize(ForwardVector);

		//Calculate Right from up and forward
		FMyVector3 RightVector = MyMathLibrary::CrossProduct(UpVector, ForwardVector);
		RightVector = MyMathLibrary::Normalize(RightVector);

		//UpVector = MyMathLibrary::CrossProduct(ForwardVector, RightVector);
		//UpVector = MyMathLibrary::Normalize(UpVector);

		//Apply properties for projectile
		Projectile->Speed = Projectile->Speed * ProjectileSpeedModifier;
		Projectile->CalculateVelocity(ForwardVector);
	}
}

void ATurret::TurretShoot()
{
	if (bCanFire == true)
	{
		//Create Projectile
		UE_LOG(LogTemp, Warning, TEXT("Fired Turret, %s"), *GetName());
		
		//Reduce turret ammo by 1 and clamp
		CurrentCapacity--;
		SpawnProjectile();
		MyMathLibrary::ClampInRange(CurrentCapacity, 0, MaxCapacity);

		if (CurrentCapacity == 0)
		{
			ReloadTurret(ReloadTime);
			CurrentCapacity = MaxCapacity;
			UE_LOG(LogTemp, Warning, TEXT("Reloading: %f, Current: %d"),ReloadTime,CurrentCapacity);
		}
		else
		{
			ReloadTurret(ShootCooldownTime);
			UE_LOG(LogTemp, Warning, TEXT("Cooldown: %f, Current: %d"), ShootCooldownTime,CurrentCapacity);
		}
	}
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
		//UE_LOG(LogTemp, Warning, TEXT("Before Clamp: %f"), BarrelPitch);
		BarrelPitch = MyMathLibrary::ClampInRange(BarrelPitch, -10, 40);
		//UE_LOG(LogTemp, Warning, TEXT("After Clamp: %f"), BarrelPitch);
		FRotator BarrelRotation = FRotator(BarrelPitch*1, Mesh->GetComponentRotation().Yaw, Mesh->GetComponentRotation().Roll);


		Barrel->SetWorldRotation(BarrelRotation, false);

		
	}
}

