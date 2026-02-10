// Fill out your copyright notice in the Description page of Project Settings.


#include "Pursuer_Char.h"
#include "Kismet/GameplayStatics.h"
#include <Evader_Char.h>

// Sets default values
APursuer_Char::APursuer_Char()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AEvade_Controller::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	USkeletalMeshComponent* CharMesh = GetMesh();
	USkeletalMesh* LoadedMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/TutorialTPP.TutorialTPP"));
	CharMesh->SetSkeletalMesh(LoadedMesh);

	//Sets offset for skeleton mesh
	FVector Location = CharMesh->GetRelativeLocation();
	Location = FVector(Location.X, Location.Y, Location.Z - 90.f);
	FRotator Rotation = CharMesh->GetRelativeRotation();
	Rotation = FRotator(Rotation.Roll, Rotation.Yaw - 90.f, Rotation.Pitch);

	CharMesh->SetRelativeLocation(Location);
	CharMesh->SetRelativeRotation(Rotation);
}

// Called when the game starts or when spawned
void APursuer_Char::BeginPlay()
{
	Super::BeginPlay();

	Evader = UGameplayStatics::GetActorOfClass(GetWorld(), AEvader_Char::StaticClass());	
}

// Called every frame
void APursuer_Char::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Evader) return;

	FMyVector3 EvaderLocation = MyMathLibrary::ConvertToCustomVector(Evader->GetActorLocation());
	FMyVector3 SelfLocation = MyMathLibrary::ConvertToCustomVector(GetActorLocation());
	
	//Minus position of target and self
	FMyVector3 Dir = MyMathLibrary::Subtract3D(EvaderLocation, SelfLocation);
	//Alternative to Movestep
	//UE_LOG(LogTemp, Warning, TEXT("Dir = %f,%f,%f"), Dir.x, Dir.y, Dir.z);
	//FMyVector3 DirNormal = MyMathLibrary::Normalize(Dir);
	//UE_LOG(LogTemp, Warning, TEXT("DirNormal = %f,%f,%f"), DirNormal.x, DirNormal.y, DirNormal.z);
	//FMyVector3 Vel = MyMathLibrary::Scale(DirNormal, 250.f);
	//UE_LOG(LogTemp, Warning, TEXT("Vel = %f,%f,%f"), Vel.x, Vel.y, Vel.z);
	//FMyVector3 Step = MyMathLibrary::Scale(Vel, DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Step = %f,%f,%f"), Step.x, Step.y, Step.z);

	FMyVector3 Step = MyMathLibrary::MoveStep(Dir, MyMathLibrary::Distance3D(EvaderLocation, SelfLocation), DeltaTime);

	FMyVector3 StepPos = MyMathLibrary::Add3D(Step, MyMathLibrary::ConvertToCustomVector(GetActorLocation()));
	
	
	FMyVector3 ToPursurer = MyMathLibrary::Normalize(MyMathLibrary::Subtract3D(SelfLocation, EvaderLocation));
	FMyVector3 EvaderVelociy = MyMathLibrary::ConvertToCustomVector(Evader->GetVelocity());
	FMyVector3 EvaderMoveDir = MyMathLibrary::Normalize(EvaderVelociy);

	float dot = MyMathLibrary::Dot(MyMathLibrary::Normalize(EvaderMoveDir), MyMathLibrary::Normalize(ToPursurer));
	UE_LOG(LogTemp, Warning, TEXT("Dot = % f"), dot);
	
	float Dist = MyMathLibrary::Distance3D(EvaderLocation, SelfLocation);
	if (dot < 0 && Dist < 2500.f)
	{
		SetActorLocation(MyMathLibrary::ConvertFromCustomVector(StepPos));
		
	}

	
	
	UE_LOG(LogTemp, Warning, TEXT("Distance = % f"), Dist);
}

// Called to bind functionality to input
void APursuer_Char::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

