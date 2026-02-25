// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipController.h"
#include "MyMathLibrary.h"


AShipController::AShipController()
{
}

void AShipController::Tick(float DeltaTime)
{ 
}

void AShipController::Look(const FMyVector2 Value)
{
	LookInput = Value;

	//look
	yawDeg += LookInput.x * LookSens;
	pitchDeg -= LookInput.y * LookSens;
	pitchDeg = FMath::Clamp(pitchDeg, -PitchClamp, PitchClamp);
}

void AShipController::Move(const FMyVector2 Value)
{
	MoveInput = Value;

	//movement
	float YawRadians = MyMathLibrary::DegreesToRadians(yawDeg);
	float PitchRadians = MyMathLibrary::DegreesToRadians(pitchDeg);

	FMyVector3 ForwardVector = MyMathLibrary::ForwardFromYawPitch(YawRadians, PitchRadians);
	ForwardVector.z = 0;
	ForwardVector = MyMathLibrary::Normalize(ForwardVector);

	//UE_LOG(LogTemp, Warning, TEXT("Forward : %f, %f, %f"),ForwardVector.x, ForwardVector.y, ForwardVector.z);

	FMyVector3 RightVector = (MyMathLibrary::CrossProduct(FMyVector3(0, 0, 1), ForwardVector));
	RightVector = MyMathLibrary::Normalize(RightVector);
	//UE_LOG(LogTemp, Warning, TEXT("Right: %f, %f, %f"), RightVector.x, RightVector.y, RightVector.z);


	FMyVector3 MoveDir = MyMathLibrary::Add3D(MyMathLibrary::Scale(ForwardVector, MoveInput.x), MyMathLibrary::Scale(RightVector, MoveInput.y));
	FMyVector3 MoveDirNormal = MyMathLibrary::Normalize(MoveDir);

	StepMovement = MyMathLibrary::MoveStep(MoveDirNormal, MoveSpeed, GetWorld()->DeltaRealTimeSeconds);
}
