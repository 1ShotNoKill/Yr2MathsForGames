// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct FMyVector2
{
	float x;
	float y;
};

struct FMyVector3
{
	float x;
	float y;
	float z;
};

class CUSTOMMATHSLIBRARY_API MyMathLibrary
{
public:
	MyMathLibrary();
	~MyMathLibrary();

	FMyVector2 ConvertToCustomVector2D(FVector2D a);
	FVector2D ConvertFromCustomVector2D(FMyVector2 a);

	/*2D Vector*/
	static FMyVector2 Add2D(FMyVector2 a, FMyVector2 b);
	static FMyVector2 Subtract2D(FMyVector2 a, FMyVector2 b);
	static float Magnitude2D(FMyVector2 v);
	static float Distance2D(FMyVector2 a, FMyVector2 b);

	/*3D Vector*/
	static FMyVector3 Add3D(FMyVector3 a, FMyVector3 b);
	static FMyVector3 Subtract3D(FMyVector3 a, FMyVector3 b);
	static float Magnitude3D(FMyVector3 v);
	static float Distance3D(FMyVector3 a, FMyVector3 b);
	static FMyVector3 Scale(FMyVector3 v, float s);
	static FMyVector3 Divide(FMyVector3 v, float s);
	static FMyVector3 Normalize(FMyVector3 v);
	static float Dot(FMyVector3 a, FMyVector3 b);
	static FMyVector3 ConvertToCustomVector(FVector3d a);
	static FVector3d ConvertFromCustomVector(FMyVector3 a);
	/*Helper functions*/
	static FMyVector3 MoveStep(FMyVector3 Direction, float Speed, float DeltaTime);

	static float DegreesToRadians(float Degrees);
	static float RadiansToDegrees(float Radians);
	static float AngleFromVector2(FMyVector2 v);
	static FMyVector2 Vector2FromAngle(float Radians);
	static FMyVector3 ForwardFromYawPitch(float YawRadians, float PitchRadians);
	static FMyVector3 CrossProduct(FMyVector3 a, FMyVector3 b);







};
