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

float MyMathLibrary::Distance3D(FMyVector3 a, FMyVector3 b)
{
	return Magnitude3D(Subtract3D(a, b));
}

FMyVector3 MyMathLibrary::Scale(FMyVector3 v, float s)
{
	return FMyVector3((v.x * s),(v.y * s), (v.z * s));
}

FMyVector3 MyMathLibrary::Divide(FMyVector3 v, float s)
{

	return FMyVector3((v.x / s), (v.y / s), (v.z / s));
}

FMyVector3 MyMathLibrary::Normalize(FMyVector3 v)
{
	float Len = Magnitude3D(v);
	if (Len == 0.f) return FMyVector3(0.f, 0.f, 0.f);
	return FMyVector3(Divide(v, Len));
}

float MyMathLibrary::Dot(FMyVector3 a, FMyVector3 b)
{
	float Dot = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
		if (Dot > 1) return 1.f;
		if (Dot < -1) return -1.f;
	return Dot;
}
//Converts from unreal vector to custom vector
FMyVector3 MyMathLibrary::ConvertToCustomVector(FVector3d a)
{
	return FMyVector3(a.X,a.Y,a.Z);
}

FVector3d MyMathLibrary::ConvertFromCustomVector(FMyVector3 a)
{
	return FVector3d(a.x,a.y,a.z);
}

FMyVector3 MyMathLibrary::MoveStep(FMyVector3 Direction, float Speed, float DeltaTime)
{
	FMyVector3 Dir = Normalize(Direction);
	FMyVector3 Vel = Scale(Dir, Speed); //units per second
	return FMyVector3(Scale(Vel,DeltaTime)); //units per frame
}
