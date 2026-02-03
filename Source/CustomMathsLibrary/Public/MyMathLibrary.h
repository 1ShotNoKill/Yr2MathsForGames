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

	static FMyVector2 Add2D(FMyVector2 a, FMyVector2 b);
	static FMyVector2 Subtract2D(FMyVector2 a, FMyVector2 b);
	static float Magnitude2D(FMyVector2 v);
	static float Distance2D(FMyVector2 a, FMyVector2 b);

	static FMyVector3 Add3D(FMyVector3 a, FMyVector3 b);
	static FMyVector3 Subtract3D(FMyVector3 a, FMyVector3 b);
	static float Magnitude3D(FMyVector3 v);
	static float Distance3D(FMyVector3 a, FMyVector3 b);
};
