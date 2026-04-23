// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyMathLibrary.h"

/**
 * 
 */

struct BoxSize
{
	float x;
	float y;
	float z;
};

class CUSTOMMATHSLIBRARY_API BoundingBox
{
public:
	BoxSize Size;
	FMyVector3 Origin;
	FMyVector3 OriginOffset;
	AActor* Owner;
	float ResponseType; /*-1 = Block, 0 = Overlap, 1 = Ignore*/



	BoundingBox();
	BoundingBox(AActor* OwningActor,FMyVector3 BoxSize, FMyVector3 BoxOffset,float Response);
	FMyVector3 GetPosition();
	FMyVector3 GetExtents();
	void DebugDrawBox();
	FMyVector3 GetDistanceBetweenBoxes(/*A = This*/ BoundingBox B);
	FMyVector3 AABBOverlap(/*A = This*/ BoundingBox B);
	void SetResponseType(float DesiredResponse);
	//void UpdateCollision(); /*Used when entity is moving*/
	
};
