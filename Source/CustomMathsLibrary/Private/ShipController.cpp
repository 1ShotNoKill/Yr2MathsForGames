// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipController.h"

AShipController::AShipController()
{

}

void AShipController::Tick(float DeltaTime)
{
	yawDeg += LookInput.x * lookSensitivity;

	pitchDeg -= lookInput.y * lookSensitivity;

	pitchDeg = Mathf.Clamp(pitchDeg, -pitchClamp, pitchClamp);
}
