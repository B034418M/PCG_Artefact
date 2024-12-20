// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PCGLandscapeSettings.generated.h"

class ALandscape;
class ULandscapeSplineSegment;
class ULandscapeComponent;
class UPCGMeshSelectorWeighted;
class APCGVolume;

struct FPCGMeshSelectorWeightedEntry;

UCLASS()
class PCG_ARTEFACT_API APCGLandscapeSettings : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APCGLandscapeSettings();

#pragma region Functions
	UFUNCTION(CallInEditor, Category = "Spline Component")
	void UpdateLandscapeSplineMeshes();

	// DEPRECATED
	UFUNCTION(CallInEditor, Category = "Spline Component")
	void UpdateForestMeshes();

	UFUNCTION()
	void CallPostEditMove();

	UFUNCTION()
	FLandscapeSplineMeshEntry CreateMeshEntry(UStaticMesh* Mesh);
#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Component | Settings")
	bool _ShowLCurb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Component | Settings")
	bool _ShowRCurb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Component | Settings")
	bool _ShowPropsWithoutCurb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Component | Settings", meta=(EditCondition="_ShowPropsWithoutCurb"))
	int _CurbPropZOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Component | Settings")
	FVector _PropGap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Component | Settings")
	bool _HasForest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Component | Setup")
	TObjectPtr<UStaticMesh> _RoadMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Component | Setup")
	TObjectPtr<UStaticMesh> _RoadMeshL;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Component | Setup")
	TObjectPtr<UStaticMesh> _RoadMeshR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Component | Setup")
	TObjectPtr<UStaticMesh> _RoadMeshLR;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Component | Setup")
	TArray<TSoftObjectPtr<UStaticMesh>> _TreeMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Component | Setup")
	TObjectPtr<ALandscape> _Landscape;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline Component | Setup")
	TArray<TObjectPtr<ULandscapeSplineSegment>> _SplineSegments;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Spline Component | Setup")
	TObjectPtr<APCGVolume> _PCGVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FPCGMeshSelectorWeightedEntry> MeshEntries;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Component | Setup")
	TSoftObjectPtr<UStaticMesh> _Mesh;
#pragma endregion	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
