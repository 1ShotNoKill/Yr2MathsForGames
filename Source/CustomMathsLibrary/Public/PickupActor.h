// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoundingBox.h"
#include "PickupActor.generated.h"

UCLASS()
class CUSTOMMATHSLIBRARY_API APickupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActor();

	BoundingBox CollisionBox;
	bool BCollisionEnabled = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
	UStaticMeshComponent* Mesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
