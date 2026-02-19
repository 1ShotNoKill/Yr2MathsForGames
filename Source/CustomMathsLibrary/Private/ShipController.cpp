// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipController.h"
#include "MyMathLibrary.h"


AShipController::AShipController()
{

}

void AShipController::Tick(float DeltaTime)
{
}

void AShipController::Update()
{
	yawDeg += LookInput.x * LookSens;
	pitchDeg -= LookInput.y * LookSens;
	pitchDeg = FMath::Clamp(pitchDeg, -PitchClamp, PitchClamp);


	float YawRadians = MyMathLibrary::DegreesToRadians(yawDeg);
	float PitchRadians = MyMathLibrary::DegreesToRadians(pitchDeg);

	FMyVector2 YawVector = MyMathLibrary::Vector2FromAngle(YawRadians);
	FMyVector2 PitchVector = MyMathLibrary::Vector2FromAngle(PitchRadians);

	FMyVector3 ForwardVector = MyMathLibrary::ForwardFromYawPitch(YawRadians, PitchRadians);
}
