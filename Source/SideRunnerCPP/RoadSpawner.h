// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "RoadSection.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "RoadSpawner.generated.h"

//class ARoadSection;
UCLASS()
class SIDERUNNERCPP_API ARoadSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoadSpawner();
	void RespawnRoads();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int32 LastSectionIndex;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION (BlueprintCallable) void SpawnSection();
	TArray <ARoadSection*> RoadSections;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)TArray<TSubclassOf<ARoadSection>> RoadClasses;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) TSubclassOf<ARoadSection> FirstRoadClass = ARoadSection::StaticClass();
	UFUNCTION(BlueprintCallable) void BoxCompOverlapped
	(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
