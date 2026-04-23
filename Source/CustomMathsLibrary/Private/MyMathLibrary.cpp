// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMathLibrary.h"
#include "MyMatrix4.h"
#include "MyQuat.h"
#include "BoundingBox.h"

MyMathLibrary::MyMathLibrary()
{
}

MyMathLibrary::~MyMathLibrary()
{
}

float MyMathLibrary::Absolute(float Value)
{
		if (Value < 0)
		{
			return Value * -1;
		}
		return Value;
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
	return FMyVector3(Scale(Vel, DeltaTime)); //units per frame
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

FMyVector3 MyMathLibrary::DirectionFromBasis(FMyVector3 localDir, FMyVector3 R, FMyVector3 U, FMyVector3 F)
{
	FMyVector3 Xr = MyMathLibrary::Scale(R,localDir.x);
	FMyVector3 Xu = MyMathLibrary::Scale(U, localDir.y);
	FMyVector3 Xf = MyMathLibrary::Scale(F, localDir.z);

	FMyVector3 Xru = MyMathLibrary::Add3D(Xr, Xu);
	FMyVector3 Xruf = MyMathLibrary::Add3D(Xru, Xf);
	return Xruf;
}

FMyVector3 MyMathLibrary::LocalPointToWorldPoint(FMyVector3 P, FMyVector3 localPoint, FMyVector3 R, FMyVector3 U, FMyVector3 F)
{
	FMyVector3 DFB = DirectionFromBasis(localPoint, R, U, F);
	FMyVector3 LPtoWP = MyMathLibrary::Add3D(DFB, P);
	return LPtoWP;
}

float MyMathLibrary::Dot4(FMyVector4 A, FMyVector4 B)
{
	float x = A.x * B.x;
	float y = A.y * B.y;
	float z = A.z * B.z;
	float w = A.w * B.w;
	return x + y + z + w;
}

void MyMathLibrary::BuildBasisFromForward(const FMyVector3& Forward, FMyVector3& R,FMyVector3& U, FMyVector3& F) //Pass by reference, sets variable values of R,U,F 
{
	F = MyMathLibrary::Normalize(Forward); //Normalise forward vector
	U = FMyVector3(0, 0, 1); //Assumes up is world up to calculate right

	R = MyMathLibrary::Normalize(MyMathLibrary::CrossProduct(U, F)); //crossing Up and Forward gives right vector
	
	U = MyMathLibrary::CrossProduct(F, R); //Re-set up to guarrantee orthogonality by using a calculated up instead of assumption
}

FMyVector3 MyMathLibrary::TransformPoint(MyMatrix4 M, FMyVector3 P)
{
	float W = 1.f; //Set W to 1 due to Point transform otherwise 0 would be calculating direction
	FMyVector4 V = FMyVector4(P.x, P.y, P.z, W); //Pack matrix column
	FMyVector4 OutV = M.Multiply(V);
		return FMyVector3(OutV.x, OutV.y, OutV.z);
}

FMyVector3 MyMathLibrary::RotateAroundAxis(FMyVector3 v, FMyVector3 axis, float angleRad)
{
	//Normalize axis
	FMyVector3 NAxis = MyMathLibrary::Normalize(axis);

	//Trig
	float CosT = FMath::Cos(angleRad);
	float SinT = FMath::Sin(angleRad);


	//Term1
	FMyVector3 Term1 = MyMathLibrary::Scale(v, CosT);

	//Term 2
	float Dot = MyMathLibrary::Dot(v, NAxis);
	FMyVector3 Term2 = MyMathLibrary::Scale(NAxis, Dot * (1.f - CosT));

	//Term 3
	FMyVector3 Cross = MyMathLibrary::CrossProduct(NAxis, v);
	FMyVector3 Term3 = MyMathLibrary::Scale(Cross, SinT);

	//Final Result
	FMyVector3 Result = MyMathLibrary::Add3D(MyMathLibrary::Add3D(Term1, Term2), Term3);

	return Result;
}








//Rotation

FRotator MyMathLibrary::AddRotation(FRotator A, FRotator B)
{
	float Pitch = A.Pitch + B.Pitch;
	float Yaw = A.Yaw + B.Yaw;
	float Roll = A.Roll + B.Roll;
		return FRotator(Pitch,Yaw,Roll);
}

FRotator MyMathLibrary::SubtractRotation(FRotator A, FRotator B)
{
	float Pitch = A.Pitch - B.Pitch;
	float Yaw = A.Yaw - B.Yaw;
	float Roll = A.Roll - B.Roll;
	return FRotator(Pitch, Yaw, Roll);
}

FRotator MyMathLibrary::MultiplyRotation(FRotator A, float B)
{
	float Pitch = A.Pitch* B;
	float Yaw = A.Yaw * B;
	float Roll = A.Roll* B;
		return FRotator(Pitch,Yaw,Roll);
}


FRotator MyMathLibrary::LinearRotatorLerp(FRotator CurrentRotation, FRotator TargetRotation, float Speed, float DeltaTime)
{
	// A + (B-A) * T * T
	// CurrentRoation + (TargetRotation - CurrentRoation) * ((Speed * DeltaTime)* (Speed * DeltaTime)
	// CurrentRotation + DeltaRotation


	FRotator BA = MyMathLibrary::SubtractRotation(TargetRotation, CurrentRotation).GetNormalized(); //Temp Normalize
	float Easing = Speed * DeltaTime;
	FRotator BAT = BA * Easing;

	FRotator Step = MyMathLibrary::AddRotation(CurrentRotation, BAT);

		return Step;
}

float MyMathLibrary::ClampInRange(float Value, float MinValue, float MaxValue)
{
	float LocalValue = Value;
	if (Value < MinValue) LocalValue = MinValue;
	else if (Value > MaxValue) LocalValue = MaxValue;
		return LocalValue;
}

void MyMathLibrary::RotateObjectAroundParent(AActor* Parent,AActor* OrbitActor,FMyVector3 OrbitOffset,FMyVector3 RotateAxis, float RotationSpeed,float DeltaTime,float& CurrentAngleDeg)
{

	if (!OrbitActor) return;

	//Step 1 Increment angle
	CurrentAngleDeg += RotationSpeed * DeltaTime;

	//Step 2 Convert To Radians
	float AngleRad = MyMathLibrary::DegreesToRadians(CurrentAngleDeg);

	//Step 3 build Quat from AxisAngle
	MyQuat Quat(RotateAxis, AngleRad);

	//Step 4 Rotate Orbit offset

	FMyVector3 Offset(OrbitOffset.x, OrbitOffset.y, OrbitOffset.z);
	FMyVector3 RotatedOffset = Quat.RotateVector(Offset);

	//step 5 apply new position
	FMyVector3 NewLocation = MyMathLibrary::Add3D(MyMathLibrary::ConvertToCustomVector(Parent->GetActorLocation()), FMyVector3(RotatedOffset.x, RotatedOffset.y, RotatedOffset.z));
	OrbitActor->SetActorLocation(MyMathLibrary::ConvertFromCustomVector(NewLocation));

	OrbitActor->SetActorRotation(Quat.ToUnrealQuat());
}


