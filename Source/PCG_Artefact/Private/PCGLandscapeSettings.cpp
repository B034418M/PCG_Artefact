// Fill out your copyright notice in the Description page of Project Settings.


#include "PCGLandscapeSettings.h"
#include "PCGLandscapeSettings.h"

#include "Landscape.h"
#include "LandscapeSplineSegment.h"
#include "PCGVolume.h"
#include "MeshSelectors/PCGMeshSelectorWeighted.h"


// Sets default values
APCGLandscapeSettings::APCGLandscapeSettings()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Check if called in editor
#if WITH_EDITOR
void APCGLandscapeSettings::UpdateLandscapeSplineMeshes()
{
	// Safety Check
	if(!_Landscape) {UE_LOG(LogTemp, Warning, TEXT("NO LANDSCAPE")); return;}

	// Empty the spline array, ready to be populated
	_SplineSegments.Empty();

	// Loop through all ULandscapeSplineSegments in the level
	TArray<TWeakObjectPtr<ULandscapeSplineSegment>> Segments;
	for(TObjectIterator<ULandscapeSplineSegment> Itr; Itr; ++Itr)
	{
		Segments.Add(TWeakObjectPtr<ULandscapeSplineSegment>(*Itr));
	}
	for (auto LandscapeSplineSegment : Segments)
	{
		// Validate and add validated ones to spline array
		if(LandscapeSplineSegment.IsValid())
		{
			_SplineSegments.Add(*LandscapeSplineSegment);
		}
	}

	// Loop through new, validated array
	for (auto LandscapeSplineSegment : _SplineSegments)
	{
		LandscapeSplineSegment->SplineMeshes.Empty();

		// Apply appropriate mesh and update the mesh on the segment
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

	// Create a timer for updating the whole landscape as it is required for some reason
	FTimerHandle CallPostEditMove;

	GetWorld()->GetTimerManager().SetTimer(CallPostEditMove, this, &APCGLandscapeSettings::CallPostEditMove, 0.5f, false);
}

void APCGLandscapeSettings::UpdateForestMeshes()
{
	// Create an FPCGMeshSelectorWeightedEntry for the tree meshes as it is required for the PCG Static Mesh Spawner
	MeshEntries.Empty();
	for (int i = 0; i < _TreeMeshes.Num(); ++i)
	{
		MeshEntries.Add(FPCGMeshSelectorWeightedEntry(_TreeMeshes[i], 1));
		UE_LOG(LogTemp, Warning, TEXT("adding %s"), *MeshEntries[i].DisplayName.ToString());
	}
}

void APCGLandscapeSettings::CallPostEditMove()
{
	// Update Landscape after delay
	_Landscape->PostEditMove(true);

	UE_LOG(LogTemp, Warning, TEXT("UPDATING"));
}

FLandscapeSplineMeshEntry APCGLandscapeSettings::CreateMeshEntry(UStaticMesh* Mesh)
{
	// Adjust specific data here if required
	// TODO: Potentially add a FLandscapeSplineMeshEntry struct to add these settings to this manager and automatically apply them here?
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

