// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMathLibrary.h"

MyMathLibrary::MyMathLibrary()
{
}

MyMathLibrary::~MyMathLibrary()
{
}

/*Vector 2 functions ---------------------------------------*/
FMyVector2 MyMathLibrary::ConvertToCustomVector2D(FVector2D a)
{
	return FMyVector2(a.X, a.Y);
}

FVector2D MyMathLibrary::ConvertFromCustomVector2D(FMyVector2 a)
{
	return FVector2d(a.x, a.y);
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






/*Vector 3 functions ---------------------------------------*/
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

float MyMathLibrary::DegreesToRadians(float Degrees)
{
	return Degrees * (PI / 180);
}

float MyMathLibrary::RadiansToDegrees(float Radians)
{
	return Radians * (180/PI);
}

float MyMathLibrary::AngleFromVector2(FMyVector2 v)
{
	
	return atan2(v.y, v.x);
}

FMyVector2 MyMathLibrary::Vector2FromAngle(float Radians)
{

	return FMyVector2((cos(Radians)),sin(Radians));
}

FMyVector3 MyMathLibrary::ForwardFromYawPitch(float YawRadians, float PitchRadians)
{
	
	float Fx = cos(PitchRadians) * cos(YawRadians);
	float Fy = sin(YawRadians) * cos(PitchRadians);
	float Fz = sin(PitchRadians);

		return FMyVector3(Fx,Fy,Fz);
}

FMyVector3 MyMathLibrary::CrossProduct(FMyVector3 a, FMyVector3 b)
{
	float Cx = (a.y * b.z) - (a.z * b.y);
	float Cy = (a.z * b.x) - (a.x * b.z);
	float Cz = (a.x * b.y) - (a.y * b.x);
	return FMyVector3(Cx,Cy,Cz);
}



FMyVector3 DirectionFromBasis(FMyVector3 localDir, FMyVector3 R, FMyVector3 U, FMyVector3 F)
{
	FMyVector3 Xr = MyMathLibrary::Scale(R,localDir.x);
	FMyVector3 Xu = MyMathLibrary::Scale(U, localDir.y);
	FMyVector3 Xf = MyMathLibrary::Scale(F, localDir.z);

	FMyVector3 Xru = MyMathLibrary::Add3D(Xr, Xu);
	FMyVector3 Xruf = MyMathLibrary::Add3D(Xru, Xf);
	return Xruf;
}


FMyVector3 LocalPointToWorldPoint(FMyVector3 P, FMyVector3 localPoint, FMyVector3 R, FMyVector3 U, FMyVector3 F)
{
	FMyVector3 DFB = DirectionFromBasis(localPoint, R, U, F);
	FMyVector3 LPtoWP = MyMathLibrary::Add3D(DFB, P);
	return LPtoWP;
}



