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
	UE_LOG(LogTemp, Warning, TEXT("--------------------------------------------"));
	
	FMyVector3 scale = MyMathLibrary::Scale(FMyVector3(2, -3, 1), 4);
	FMyVector3 Divide = MyMathLibrary::Divide(FMyVector3(6, -2, 10),2);
	FMyVector3 Normalize = MyMathLibrary::Normalize(FMyVector3(3, 4, 0));
	float Dot = MyMathLibrary::Dot(FMyVector3(0, 1, 0), FMyVector3(0, 1, 0));
	float Dot1 = MyMathLibrary::Dot(FMyVector3(0, 1, 0), FMyVector3(1, 0, 0));
	float Dot2 = MyMathLibrary::Dot(FMyVector3(0, 1, 0), FMyVector3(0, -1, 0));
	FMyVector3 Normalize0 = MyMathLibrary::Normalize(FMyVector3(0, 0, 0));
	
	UE_LOG(LogTemp, Warning, TEXT("Scale = %f,%f,%f"),scale.x,scale.y,scale.z);
	UE_LOG(LogTemp, Warning, TEXT("Divide = %f,%f,%f"), Divide.x, Divide.y, Divide.z);
	UE_LOG(LogTemp, Warning, TEXT("Normalize = %f,%f,%f"), Normalize.x, Normalize.y, Normalize.z);
	UE_LOG(LogTemp, Warning, TEXT("%f"), Dot);
	UE_LOG(LogTemp, Warning, TEXT("%f"), Dot1);
	UE_LOG(LogTemp, Warning, TEXT("%f"), Dot2);
	UE_LOG(LogTemp, Warning, TEXT("Normalize = %f,%f,%f"), Normalize0.x, Normalize0.y, Normalize0.z);
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

