// Fill out your copyright notice in the Description page of Project Settings.


#include "MatrixCube.h"

// Sets default values
AMatrixCube::AMatrixCube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UStaticMeshComponent* MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Models/Boat.Boat");
	MeshComp->SetStaticMesh(Mesh);
}

// Called when the game starts or when spawned
void AMatrixCube::BeginPlay()
{
	Super::BeginPlay();
	
	
	YawRad = 0.f;
	PitchRad = 0.f;
	P = FMyVector3(0, 0, 0);
}

// Called every frame
void AMatrixCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	YawRad = YawRad + MyMathLibrary::DegreesToRadians(YawSpeedDeg) * DeltaTime;
	PitchRad = PitchRad + MyMathLibrary::DegreesToRadians(PitchRad) * DeltaTime;

	FMyVector3 F = MyMathLibrary::ForwardFromYawPitch(YawRad, PitchRad);
	P = MyMathLibrary::Add3D(P, MyMathLibrary::Scale(F, MoveSpeed * DeltaTime));
}

