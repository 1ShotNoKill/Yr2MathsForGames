// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbitActor.h"

// Sets default values
AOrbitActor::AOrbitActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube")));
}

// Called when the game starts or when spawned
void AOrbitActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (OrbitingObject)
	{
		OrbitingObject->SetActorLocation(GetActorLocation() +MyMathLibrary::ConvertFromCustomVector(OrbitOffset));
	}
}

// Called every frame
void AOrbitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!OrbitingObject) return;

	//Step 1 Increment angle
	CurrentAngleDeg += DegreePerSecond * DeltaTime;

	//Step 2 Convert To Radians
	float AngleRad = MyMathLibrary::DegreesToRadians(CurrentAngleDeg);

	//Step 3 build Quat from AxisAngle
	MyQuat Quat(Axis, AngleRad);

	//Step 4 Rotate Orbit offset

	FMyVector3 Offset(OrbitOffset.x, OrbitOffset.y, OrbitOffset.z);
	FMyVector3 RotatedOffset = Quat.RotateVector(Offset);

	//step 5 apply new position
	FMyVector3 NewLocation = MyMathLibrary::Add3D(MyMathLibrary::ConvertToCustomVector(GetActorLocation()), FMyVector3(RotatedOffset.x, RotatedOffset.y, RotatedOffset.z));
	OrbitingObject->SetActorLocation(MyMathLibrary::ConvertFromCustomVector(NewLocation));

	OrbitingObject->SetActorRotation(Quat.ToUnrealQuat());
}

