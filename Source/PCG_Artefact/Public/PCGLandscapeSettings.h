// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PCGLandscapeSettings.generated.h"

class ALandscape;
class ULandscapeSplineSegment;class ULandscapeComponent;

UCLASS()
class PCG_ARTEFACT_API APCGLandscapeSettings : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APCGLandscapeSettings();

	UFUNCTION(CallInEditor, Category = "Spline Component")
	void UpdateLandscapeSplineMeshes();

	UFUNCTION()
	FLandscapeSplineMeshEntry CreateMeshEntry(UStaticMesh* Mesh);

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline Component")
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _ShowLCurb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _ShowRCurb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> _RoadMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> _RoadMeshL;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> _RoadMeshR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> _RoadMeshLR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ALandscape> _Landscape;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<ULandscapeSplineSegment>> _SplineSegments;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
