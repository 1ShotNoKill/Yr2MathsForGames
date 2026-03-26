// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyMathLibrary.h"
#include "Turret.generated.h"

UCLASS()
class CUSTOMMATHSLIBRARY_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();
	FMyVector3 LocalOffset;

	UFUNCTION()
	void TurretShoot();
	FMyVector3 PosOffset;
	FString TurretBase;
	FString TurretBarrel;
	FMyVector3 ProjectileSpawnOffset;
	float ProjectileSpeedModifier = 1;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	void ReloadTurret(float Time);
	void SpawnProjectile();
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY()
	UStaticMeshComponent* Barrel;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	float DegClamp = 80; //Defines Max Rotation
	float BaseTurretRotationSpeed = 0.75; //Defines base speed at which the turret can rotate
	int MaxCapacity = 2; //Defines Max capacity of turret before needing reload
	int CurrentCapacity = 2; //Defines current ammo in turret
	float ReloadTime = 5; //Defines time it takes to reload capacity
	bool bCanFire = true;
	float ShootCooldownTime = 1; //Defines time between shots
	

	class AShipController* ShipController;
	class AShip_Character* PlayerShip;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetShipCharacterReference(AShip_Character* OwningShip);
};
