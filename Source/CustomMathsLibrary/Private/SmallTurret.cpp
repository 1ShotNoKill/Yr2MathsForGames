// Fill out your copyright notice in the Description page of Project Settings.


#include "SmallTurret.h"

ASmallTurret::ASmallTurret()
{
	TurretBase = "/Game/Models/SmallTurretBase.SmallTurretBase";
	TurretBarrel = "/Game/Models/SmallTurretBarrels.SmallTurretBarrels";

	DegClamp = 80;
	BaseTurretRotationSpeed = 2; //Defines base speed at which the turret can rotate
	MaxCapacity = 100; //Defines Max capacity of turret before needing reload
	CurrentCapacity = 100; //Defines current ammo in turret
	ReloadTime = 2.5; //Defines time it takes to reload capacity
	ShootCooldownTime = 0.1; //Defines time between shots
	ProjectileSpeedModifier = 0.5; //Defines projectile Speed multiplier
}

void ASmallTurret::BeginPlay()
{
	Super::BeginPlay();
}
