// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyMathLibrary.h"
#include "MatrixCube.generated.h"

UCLASS()
class CUSTOMMATHSLIBRARY_API AMatrixCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMatrixCube();
	UPROPERTY(EditAnywhere, Category = "Angles");
	float YawSpeedDeg = 90.f;
	UPROPERTY(EditAnywhere, Category = "Angles");
	float PitchSpeedDeg = 30.f;

	UPROPERTY(EditAnywhere, Category = "Movement");
	float MoveSpeed = 2.f;

	//UPROPERTY(EditAnywhere, Category = "Scale");
	//FVector3D nonUniformScale = FVector3.one;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Mesh
	UStaticMesh* Mesh;
	FMyVector3 OriginalVerts;
	FMyVector3 DeformedVerts;

	//Transform each frame
	float YawRad;
	float PitchRad;
	FMyVector3 P;

	



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
