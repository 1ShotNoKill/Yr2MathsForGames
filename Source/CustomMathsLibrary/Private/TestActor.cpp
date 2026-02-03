// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	FMyVector2 Add = MyMathLibrary::Add2D(FMyVector2(-3,4),FMyVector2(5,-2));
	FMyVector2 Sub = MyMathLibrary::Subtract2D(FMyVector2(2, 5), FMyVector2(5, 3));
	float Mag = MyMathLibrary::Magnitude2D(FMyVector2(3, 4));
	float Dist = MyMathLibrary::Distance2D(FMyVector2(2, 3), FMyVector2(8, 0));

	UE_LOG(LogTemp, Warning, TEXT("%f, %f"), Add.x,Add.y);
	UE_LOG(LogTemp, Warning, TEXT("%f, %f"), Sub.x,Sub.y);
	UE_LOG(LogTemp, Warning, TEXT("%f"), Mag);
	UE_LOG(LogTemp, Warning, TEXT("%f"), Dist);
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

