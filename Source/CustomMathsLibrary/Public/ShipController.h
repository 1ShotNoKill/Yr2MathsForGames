// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyMathLibrary.h"

#include "ShipController.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMMATHSLIBRARY_API AShipController : public APlayerController
{
	GENERATED_BODY()
	AShipController();

public:
	UPROPERTY(EditAnywhere, Category = "Tuning");
	float MoveSpeed = 20.f;
	UPROPERTY(EditAnywhere, Category = "Tuning");
	float LookSens = 0.5f;
	UPROPERTY(EditAnywhere, Category = "Tuning");
	float PitchClamp = 80.f;


	FMyVector2 MoveInput; //X,Y
	FMyVector2 LookInput; //Mouse Delta
	float yawDeg;
	float pitchDeg;
	FMyVector3 StepMovement;



	void Look(const FMyVector2 Value);
	void Move(const FMyVector2 Value);
	virtual void Tick(float DeltaTime) override;
	void Update(float DeltaTime);
};
