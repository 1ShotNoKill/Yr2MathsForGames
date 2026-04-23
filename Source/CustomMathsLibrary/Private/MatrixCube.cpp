// Fill out your copyright notice in the Description page of Project Settings.


#include "MatrixCube.h"
#include "MyMatrix4.h"

// Sets default values
AMatrixCube::AMatrixCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

}

// Called when the game starts or when spawned
void AMatrixCube::BeginPlay()
{
	Super::BeginPlay();
	
	YawRad = 0;
	PitchRad = 0;
	P = FMyVector3(0, 0, 0);

	ProcMeshComp = NewObject<UProceduralMeshComponent>(this, TEXT("ProcMeshComp"));
	ProcMeshComp->RegisterComponent();
	ProcMeshComp->AttachToComponent(SceneComp,FAttachmentTransformRules::KeepRelativeTransform);
	ProcMeshComp->CreateMeshSection_LinearColor(0, OriginalVerts, Tris, Normals, UVs,Colours, Tangents,false);
}

// Called every frame
void AMatrixCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	YawRad = YawRad + MyMathLibrary::DegreesToRadians(YawSpeedDeg) * DeltaTime;
	PitchRad = PitchRad + MyMathLibrary::DegreesToRadians(PitchSpeedDeg) * DeltaTime;

	//Calculate forward from radians
	FMyVector3 ForwardVector = MyMathLibrary::ForwardFromYawPitch(YawRad, PitchRad);

	//translate position
	P = MyMathLibrary::MoveStep(ForwardVector, MoveSpeed, DeltaTime);

	//build basis
	FMyVector3 R;
	FMyVector3 U;
	FMyVector3 F;
	MyMathLibrary::BuildBasisFromForward(ForwardVector, R, U, F);

	R = MyMathLibrary::Scale(R, NonUniformScale.x);
	U = MyMathLibrary::Scale(R, NonUniformScale.y);
	F = MyMathLibrary::Scale(R, NonUniformScale.z);

	MyMatrix4 Matrix;
	Matrix.SetAxes(R, U, F, P);

	


	DeformedVerts.SetNum(OriginalVerts.Num());

	for (int32 Index = 0; Index < OriginalVerts.Num(); Index++)
	{
	 MyMathLibrary::ConvertToCustomVector(DeformedVerts[Index]) = MyMathLibrary::TransformPoint(Matrix, MyMathLibrary::ConvertToCustomVector(OriginalVerts[Index]));
	}

	//ProcMeshComp->Modify();
	//MeshComp->Modify();
	//MeshComp->SetWorldLocation(MyMathLibrary::ConvertFromCustomVector(P));
	

	//ProcMeshComp->UpdateMeshSection_LinearColor(0,DeformedVerts,Normals,UVs,Colours,Tangents,false);


}

