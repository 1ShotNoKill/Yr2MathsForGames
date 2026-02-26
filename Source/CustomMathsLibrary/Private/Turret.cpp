// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Kismet/GameplayStatics.h"




// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LocalOffset = FMyVector3(0, -1, 0);

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	if(RootComponent) RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	if(Root) Mesh->SetupAttachment(Root);
	Mesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr,TEXT("/Game/Models/Turret.Turret")));
	Mesh->SetRelativeRotation(FRotator(0, 90, 0));
	Mesh->SetRelativeLocation(FVector(0, 15.5, 0));
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShip_Character::StaticClass(), FoundActors);

	PlayerShip = Cast<AShip_Character>(FoundActors[0]);
	ShipController = PlayerShip->CustomGetController();
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerShip && ShipController)
	{
		FMyVector3 R = ShipController->RightVector;
		FMyVector3 U = ShipController->UpVector;
		FMyVector3 F = ShipController->ForwardVector;

		FMyVector3 P = MyMathLibrary::ConvertToCustomVector(PlayerShip->GetActorLocation());

		FMyVector3 DFB = MyMathLibrary::DirectionFromBasis(LocalOffset, R, U, F);
	}
}

