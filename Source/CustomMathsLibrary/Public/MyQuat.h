// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyMathLibrary.h"


class CUSTOMMATHSLIBRARY_API MyQuat
{
public:
	float w;
	float x;
	float y;
	float z;

	MyQuat();
	MyQuat(float Inw, float Inx, float Iny, float Inz);
	MyQuat(FMyVector3 V);
	MyQuat(FMyVector3 Axis, float AngleRad);
	MyQuat operator *(const MyQuat& B);

	MyQuat Inverse();
	FMyVector3 RotateVector(FMyVector3 V);

	FQuat ToUnrealQuat();

};
