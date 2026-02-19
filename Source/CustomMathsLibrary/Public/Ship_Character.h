// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <ShipController.h>


#include "Ship_Character.generated.h"

UCLASS()
class CUSTOMMATHSLIBRARY_API AShip_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShip_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
	UInputMappingContext* ShipMappingContext;
	UPROPERTY()
	TMap<FName,const UInputAction*> InputActions;
	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY()
	UCameraComponent* Camera;
	UPROPERTY()
	USpringArmComponent* SpringArm;
	UPROPERTY()
	AShipController* Controller;

	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
