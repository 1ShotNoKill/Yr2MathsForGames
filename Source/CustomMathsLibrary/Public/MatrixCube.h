// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "MyMathLibrary.h"
#include "MatrixCube.generated.h"

UCLASS()
class CUSTOMMATHSLIBRARY_API AMatrixCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMatrixCube();

	UPROPERTY(EditAnywhere)
	USceneComponent* SceneComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Angles")
	float YawSpeedDeg = 90.f;
	UPROPERTY(EditAnywhere, Category = "Angles")
	float PitchSpeedDeg = 30.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 200.f;
	FMyVector3 NonUniformScale = FMyVector3(1, 1, 1);

private:

	UStaticMeshComponent* MeshComp;
	UPROPERTY(EditAnywhere)
	UProceduralMeshComponent* ProcMeshComp;

	TArray<FVector>OriginalVerts = { {0,0,0},{0,100,0},{100,100,0},{100,0,0},{0,0,100},{0,100,100},{100,100,100},{100,0,100} };

	TArray<int32> Tris = { 0,2,1, 0,3,2, 4,5,6, 4,6,7, 0,1,5, 0,5,4, 2,3,7, 2,7,6, 0,4,7, 0,7,3, 1,2,6, 1,6,5 };
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> Colours;
	TArray<FProcMeshTangent> Tangents;

	TArray<FVector> DeformedVerts;

	float YawRad;
	float PitchRad;
	FMyVector3 P; //World Position


};
