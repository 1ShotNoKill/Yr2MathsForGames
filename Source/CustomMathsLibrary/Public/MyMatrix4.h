// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyMathLibrary.h"

class CUSTOMMATHSLIBRARY_API MyMatrix4
{
	FMyVector4 Row0;
	FMyVector4 Row1;
	FMyVector4 Row2;
	FMyVector4 Row3;
public:
	void SetAxes(FMyVector3 R, FMyVector3 U, FMyVector3 F, FMyVector3 P)
	{
		Row0 = FMyVector4(R.x, U.x, F.x, P.x);
		Row1 = FMyVector4(R.y, U.y, F.y, P.y);
		Row2 = FMyVector4(R.z, U.z, F.z, P.z);
		Row3 = FMyVector4(0, 0, 0, 1);
	}

	FMyVector4 Multiply(const FMyVector4 v)
	{
		
		float x = MyMathLibrary::Dot4(Row0, v);
		float y = MyMathLibrary::Dot4(Row1, v);
		float z = MyMathLibrary::Dot4(Row2, v);
		float w = MyMathLibrary::Dot4(Row3, v);
		return FMyVector4(x, y, z, w);
	}
};
