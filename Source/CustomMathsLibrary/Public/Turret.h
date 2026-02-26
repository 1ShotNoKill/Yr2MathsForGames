// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyMathLibrary.h"
#include "Ship_Character.h"
#include "Turret.generated.h"

UCLASS()
class CUSTOMMATHSLIBRARY_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();
	FMyVector3 LocalOffset;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AShipController* ShipController;
	AShip_Character* PlayerShip;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
