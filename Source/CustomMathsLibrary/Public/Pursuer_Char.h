// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "Evade_Controller.h"

#include "MyMathLibrary.h"

#include "Pursuer_Char.generated.h"

UCLASS()
class CUSTOMMATHSLIBRARY_API APursuer_Char : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APursuer_Char();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	AActor* Evader;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
