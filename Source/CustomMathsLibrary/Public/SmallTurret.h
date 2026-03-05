// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turret.h"
#include "SmallTurret.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMMATHSLIBRARY_API ASmallTurret : public ATurret
{
	GENERATED_BODY()
	
public:
	FMyVector3 PosOffset = FMyVector3(100, 0, 0);

	FString TurretBase = "/Game/Models/SmallTurretBase.SmallTurretBase";
	FString TurretBarrel = "/Game/Models/SmallTurretBarrels.SmallTurretBarrels";

};
