// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMathLibrary.h"

MyMathLibrary::MyMathLibrary()
{
}

MyMathLibrary::~MyMathLibrary()
{
}

FMyVector2 MyMathLibrary::Add2D(FMyVector2 a, FMyVector2 b)
{
	return FMyVector2((a.x+b.x),(a.y+b.y));
}

FMyVector2 MyMathLibrary::Subtract2D(FMyVector2 a, FMyVector2 b)
{
	return FMyVector2((a.x-b.x),(a.y-b.y));
}

float MyMathLibrary::Magnitude2D(FMyVector2 v)
{
	return sqrt((v.x * v.x) + (v.y * v.y));
}

float MyMathLibrary::Distance2D(FMyVector2 a, FMyVector2 b)
{
	float temp = Magnitude2D(Subtract2D(a, b));
		UE_LOG(LogTemp, Warning, TEXT("%f"), temp);
	return Magnitude2D(Subtract2D(a, b));
}

FMyVector3 MyMathLibrary::Add3D(FMyVector3 a, FMyVector3 b)
{
	return FMyVector3((a.x + b.x),(a.y + b.y),(a.z + b.z));
}

FMyVector3 MyMathLibrary::Subtract3D(FMyVector3 a, FMyVector3 b)
{
	return FMyVector3((a.x - b.x), (a.y - b.y), (a.z - b.z));
}

float MyMathLibrary::Magnitude3D(FMyVector3 v)
{
	return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}


