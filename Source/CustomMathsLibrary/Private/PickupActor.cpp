// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupActor.h"


// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Models/Shield.Shield")));
	Mesh->SetWorldScale3D(FVector(0.25, 0.25, 0.25));

	

	UStaticMeshComponent* Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoundingBox Box(this, FMyVector3(50.f, 50.f, 50.f), FMyVector3(0,0,0),0);
	CollisionBox = Box;
	
	

}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (BCollisionEnabled)
	{
		CollisionBox.DebugDrawBox();
	}

	
}

