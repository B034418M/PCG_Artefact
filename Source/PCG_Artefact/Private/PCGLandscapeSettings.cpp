// Fill out your copyright notice in the Description page of Project Settings.


#include "PCGLandscapeSettings.h"

#include "Landscape.h"
#include "LandscapeSplineSegment.h"

// Sets default values
APCGLandscapeSettings::APCGLandscapeSettings()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

#if WITH_EDITOR
void APCGLandscapeSettings::UpdateLandscapeSplineMeshes()
{
	if(!_Landscape) {UE_LOG(LogTemp, Warning, TEXT("NO LANDSCAPE")); return;}

	// BREAKS THE LANDSCAPE!!
	//_Landscape->PreEditUndo();

	_SplineSegments.Empty();

	TArray<TWeakObjectPtr<ULandscapeSplineSegment>> Segments;
	for(TObjectIterator<ULandscapeSplineSegment> Itr; Itr; ++Itr)
	{
		Segments.Add(TWeakObjectPtr<ULandscapeSplineSegment>(*Itr));
	}
	for (auto LandscapeSplineSegment : Segments)
	{
		if(LandscapeSplineSegment.IsValid())
		{
			_SplineSegments.Add(*LandscapeSplineSegment);
		}
	}

	// if has more than 2 connections, dont change so that can add not so modular junctions :)
	for (auto LandscapeSplineSegment : _SplineSegments)
	{
		LandscapeSplineSegment->SplineMeshes.Empty();

		if(!_ShowLCurb && !_ShowRCurb)
		{
			LandscapeSplineSegment->SplineMeshes.Add(CreateMeshEntry(_RoadMesh));
			LandscapeSplineSegment->PostEditChange();
		}
		else if(_ShowLCurb && !_ShowRCurb)
		{
			LandscapeSplineSegment->SplineMeshes.Add(CreateMeshEntry(_RoadMeshL));
			LandscapeSplineSegment->PostEditChange();
		}
		else if(!_ShowLCurb && _ShowRCurb)
		{
			LandscapeSplineSegment->SplineMeshes.Add(CreateMeshEntry(_RoadMeshR));
			LandscapeSplineSegment->PostEditChange();
		}
		else if(_ShowLCurb && _ShowRCurb)
		{
			LandscapeSplineSegment->SplineMeshes.Add(CreateMeshEntry(_RoadMeshLR));
			LandscapeSplineSegment->PostEditChange();
		}
	}

	FTimerHandle CallPostEditMove;

	GetWorld()->GetTimerManager().SetTimer(CallPostEditMove, this, &APCGLandscapeSettings::CallPostEditMove, 0.5f, false);
}

void APCGLandscapeSettings::CallPostEditMove()
{
	_Landscape->PostEditMove(true);

	UE_LOG(LogTemp, Warning, TEXT("UPDATING"));
}

FLandscapeSplineMeshEntry APCGLandscapeSettings::CreateMeshEntry(UStaticMesh* Mesh)
{
	FLandscapeSplineMeshEntry data;

	// Change other data here!
	data.Mesh = Mesh;
	//data.Scale =
	//data.CenterAdjust =
	// etc
	
	return data;
}
#endif

// Called when the game starts or when spawned
void APCGLandscapeSettings::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APCGLandscapeSettings::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

