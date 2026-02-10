// Fill out your copyright notice in the Description page of Project Settings.


#include "Evader_Char.h"



// Sets default values
AEvader_Char::AEvader_Char()
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
void AEvader_Char::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<AAIController>(GetController());
	NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEvader_Char::MoveToRandomLocation, FMath::RandRange(1, 3), true);

	
}

void AEvader_Char::MoveToRandomLocation()
{
	if (NavSystem)
	{
		FNavLocation NavLoc;
		NavSystem->GetRandomPointInNavigableRadius(GetActorLocation(), 500.f, NavLoc);
		AIController->MoveToLocation(NavLoc.Location);
	}
}

// Called every frame
void AEvader_Char::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector3d VelVector = GetVelocity();
	Velocity = FMyVector3(VelVector.X, VelVector.Y, VelVector.Z);
}

// Called to bind functionality to input
void AEvader_Char::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

