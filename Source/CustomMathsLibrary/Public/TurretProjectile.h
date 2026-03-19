// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyMathLibrary.h"
#include "TurretProjectile.generated.h"

UCLASS()
class CUSTOMMATHSLIBRARY_API ATurretProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretProjectile();
	float Speed = 4000.f;
	float Lifetime = 3.f;
	FMyVector3 Velocity;
	FMyVector3 Gravity = FMyVector3(0, 0, -980);

	//FMyVector3 ForwardVector;
	//FMyVector3 RightVector;
	//FMyVector3 UpVector;
	//FMyVector3 MoveDir;

	void CalculateVelocity(FMyVector3 ForwardVector);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void DestroyProjectile();
	FTimerHandle TimerHandle;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
