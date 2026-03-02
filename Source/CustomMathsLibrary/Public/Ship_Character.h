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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShotTurret, const FInputActionValue&, Value);

UCLASS()
class CUSTOMMATHSLIBRARY_API AShip_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShip_Character();

	AShipController* CustomGetController();

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(BlueprintAssignable)
	FOnShotTurret OnShot;


	float ShipSpeed = 40.f;
	float RotationSpeed = 2.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
	UInputMappingContext* ShipMappingContext;
	UPROPERTY()
	TMap<FName,const UInputAction*> InputActions;
	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY();
	AShipController* ShipController;


	void SetDefaults();
	

	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Shoot(const FInputActionValue& Value);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
