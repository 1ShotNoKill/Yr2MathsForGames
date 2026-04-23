// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyMathLibrary.h"
#include "MyQuat.h"
#include "OrbitActor.generated.h"

UCLASS()
class CUSTOMMATHSLIBRARY_API AOrbitActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrbitActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;

	//Orbit Object#
	UPROPERTY(EditAnywhere)
	AActor* OrbitingObject;

	//Rotation Axis
	FMyVector3 Axis = FMyVector3(0, 0, 1);
	float DegreePerSecond = 45.f;
	FMyVector3 OrbitOffset = FMyVector3(200, 0, 0);
private:
	float CurrentAngleDeg = 0; //Tracks rotation


};
