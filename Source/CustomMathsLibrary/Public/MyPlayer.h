// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>

#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

#include "MyPlayer.generated.h"

UCLASS()
class CUSTOMMATHSLIBRARY_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* PlayerMappingContext; //Context used by the player for input actions

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TMap<FName, const UInputAction*> InputActions; //Stores action inputs with linked name


	void SpawnCamera();

	void TeleportPlayer();

	void Move(const FInputActionValue& Value);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
