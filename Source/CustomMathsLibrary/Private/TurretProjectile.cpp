// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretProjectile.h"

// Sets default values
ATurretProjectile::ATurretProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FString MeshPath = "/Engine/BasicShapes/Cylinder";

	UStaticMeshComponent* Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	Mesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *MeshPath));
	Mesh->SetRelativeScale3D(FVector(0.07, 0.07, 0.07));
	Mesh->SetRelativeRotation(FRotator(-90, 0, 0));
	RootComponent = Mesh;
}

void ATurretProjectile::CalculateVelocity(FMyVector3 ForwardVector)
{
	Velocity = MyMathLibrary::Scale(ForwardVector, Speed);
}

// Called when the game starts or when spawned
void ATurretProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	//Set Timer for destruction based on lifetime
	GetWorldTimerManager().SetTimer(TimerHandle,this, &ThisClass::DestroyProjectile, Lifetime, false, Lifetime);	
}

void ATurretProjectile::DestroyProjectile()
{
	this->Destroy();
}

// Called every frame
void ATurretProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FMyVector3 ActorLoc = MyMathLibrary::ConvertToCustomVector(GetActorLocation()); //Actor world location
	
	//Gravity calculations
	FMyVector3 GravityPerFrame = MyMathLibrary::Scale(Gravity, DeltaTime); //calculate gravity per frame
	Velocity = MyMathLibrary::Add3D(Velocity,GravityPerFrame); //applies gravity per frame to velocity


	FMyVector3 Step = MyMathLibrary::Scale(Velocity, DeltaTime); //scale by deltatime to get movement per frame
	SetActorLocation(MyMathLibrary::ConvertFromCustomVector(MyMathLibrary::Add3D(ActorLoc, Step))); //Add movement per frame to current position
}

