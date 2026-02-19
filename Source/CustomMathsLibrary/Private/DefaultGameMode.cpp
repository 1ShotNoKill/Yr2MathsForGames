// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameMode.h"
#include "Ship_Character.h"
#include "ShipController.h"

ADefaultGameMode::ADefaultGameMode()
{
	DefaultPawnClass = AShip_Character::StaticClass();
	PlayerControllerClass = AShipController::StaticClass();
}
