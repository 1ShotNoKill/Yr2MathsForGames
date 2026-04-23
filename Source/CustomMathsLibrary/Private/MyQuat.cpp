// Fill out your copyright notice in the Description page of Project Settings.


#include "MyQuat.h"

MyQuat::MyQuat()
{
	w = 1;
	x = 0;
	y = 0;
	z = 0;
}

MyQuat::MyQuat(float Inw, float Inx, float Iny, float Inz)
{
	w = Inw;
	x = Inx;
	y = Iny;
	z = Inz;
}

MyQuat::MyQuat(FMyVector3 V)
{
	w = 0;
	x = V.x;
	y = V.y;
	z = V.z;
}

MyQuat::MyQuat(FMyVector3 Axis, float AngleRad) 
{
	FMyVector3 NAxis = MyMathLibrary::Normalize(Axis);

	float HalfAngle = AngleRad * 0.5f;
	w = cos(HalfAngle);
	x = Axis.x * sin(HalfAngle);
	y = Axis.y * sin(HalfAngle);
	z = Axis.z * sin(HalfAngle);
}

MyQuat MyQuat::operator*(const MyQuat& B)
{
	MyQuat Result;

	Result.w = w * B.w - (x * B.x + y * B.y + z * B.z);

	Result.x = w * B.x + B.w * x + (y * B.z - z * B.y);
	Result.y = w * B.y + B.w * y + (z * B.x - x * B.z);
	Result.z = w * B.z + B.w * z + (x * B.y - y * B.x);

	return Result;
}

MyQuat MyQuat::Inverse()
{
	return MyQuat(w, -x, -y, -z);
}

FMyVector3 MyQuat::RotateVector(FMyVector3 V)
{
	MyQuat P(V); //pure quaternion

	MyQuat RotatedQuat = (*this) * P * this->Inverse();

	return FMyVector3(RotatedQuat.x, RotatedQuat.y, RotatedQuat.z);
}

FQuat MyQuat::ToUnrealQuat()
{
	return FQuat(x, y, z, w);
}
