// Fill out your copyright notice in the Description page of Project Settings.


#include "BoundingBox.h"
#include <Kismet/GameplayStatics.h>
#include "BoundingBoxInterface.h"

BoundingBox::BoundingBox()
{
}

BoundingBox::BoundingBox(AActor* OwningActor, FMyVector3 BoxSize, FMyVector3 BoxOffset, float Response)
{
	Owner = OwningActor;
	Size.x = BoxSize.x;
	Size.y = BoxSize.y;
	Size.z = BoxSize.z;
	OriginOffset = BoxOffset;
	ResponseType = Response;
}

FMyVector3 BoundingBox::GetPosition()
{
	FMyVector3 WorldPosition = MyMathLibrary::ConvertToCustomVector(Owner->GetActorLocation());
		return MyMathLibrary::Add3D(WorldPosition,OriginOffset);
}

FMyVector3 BoundingBox::GetExtents()
{
	float XExtent = Size.x / 2;
	float YExtent = Size.y / 2;
	float ZExtent = Size.z / 2;
		return FMyVector3(XExtent,YExtent,ZExtent);
}

void BoundingBox::DebugDrawBox()
{
	DrawDebugBox(Owner->GetWorld(), MyMathLibrary::ConvertFromCustomVector(GetPosition()), MyMathLibrary::ConvertFromCustomVector(GetExtents()),/*Owner->GetActorQuat(),*/ FColor::Black, false, 0, 1, 1.f);
}

FMyVector3 BoundingBox::GetDistanceBetweenBoxes(BoundingBox B)
{
	FMyVector3 Distance = MyMathLibrary::Subtract3D(GetPosition(), B.GetPosition());
		return Distance;
}

FMyVector3 BoundingBox::AABBOverlap(BoundingBox B)
{
	FMyVector3 AExtents = GetExtents();
	FMyVector3 BExtents = B.GetExtents();
	FMyVector3 Distance = GetDistanceBetweenBoxes(B);
	/*Both boxes extents are added together to create the max distance from the center before they are touching*/
	/*then we subtract the distance from this giving the distance from both boxes (Negative value = overlap)*/
	float XOverlap = (AExtents.x + BExtents.x) - MyMathLibrary::Absolute(Distance.x);
	float YOverlap = (AExtents.y + BExtents.y) - MyMathLibrary::Absolute(Distance.y);
	float ZOverlap = (AExtents.z + BExtents.z) - MyMathLibrary::Absolute(Distance.z);
	UE_LOG(LogTemp, Warning, TEXT("X:%f,Y:%f,Z:%f"), XOverlap, YOverlap, ZOverlap);	
		return FMyVector3(XOverlap,YOverlap,ZOverlap);
}

void BoundingBox::SetResponseType(float DesiredResponse)
{
	ResponseType = DesiredResponse;
}

/*Get all actors that implement interface*/
/*Distance check if above extents do nothing else*/


//void BoundingBox::UpdateCollision()
//{
//	TArray<AActor*> OutActors;
//	UGameplayStatics::GetAllActorsWithInterface(Owner->GetWorld(), UBoundingBoxInterface::StaticClass(), OutActors);
//
//	for (AActor* Actor : OutActors)
//	{
//		
//	}
//}
