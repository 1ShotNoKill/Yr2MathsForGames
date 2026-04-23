// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipEnemy.h"

// Sets default values
AShipEnemy::AShipEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*Ship Mesh*/
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetRelativeRotation(FRotator(0, 90, 0));
	StaticMeshComponent->SetRelativeLocation(FVector(0, 0, -10));
	if (RootComponent) StaticMeshComponent->SetupAttachment(RootComponent);

	UStaticMesh* LoadedMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Models/Boat.Boat"));
	if (LoadedMesh) StaticMeshComponent->SetStaticMesh(LoadedMesh);


}

// Called when the game starts or when spawned
void AShipEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	BoundingBox Box(this, FMyVector3(100.f, 60.f, 75.f), FMyVector3(0, 0, 35),-1);
	CollisionBox = Box;
}

// Called every frame
void AShipEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CollisionBox.DebugDrawBox();
}

// Called to bind functionality to input
void AShipEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

