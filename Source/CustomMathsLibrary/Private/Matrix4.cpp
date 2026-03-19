#include "Matrix4.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "Matrix4.h"

Matrix4::Matrix4()
{
}

Matrix4::~Matrix4()
{
}

FMyVector4 Matrix4::Multiply(FMyVector4 v)
{
	float x = MyMathLibrary::Dot4(Row0, v);
	float y = MyMathLibrary::Dot4(Row1, v);
	float z = MyMathLibrary::Dot4(Row2, v);
	float w = MyMathLibrary::Dot4(Row3, v);
		return FMyVector4();
}
