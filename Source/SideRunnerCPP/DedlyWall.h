// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "RunnerCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DedlyWall.generated.h"

UCLASS()
class SIDERUNNERCPP_API ADedlyWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADedlyWall();
	UPROPERTY(EditDefaultsOnly)UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)float YSpeed=500;
	UFUNCTION(BlueprintCallable) void WallOverlapped(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	ARunnerCharacter* PlayerCharacter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void StartFunction();

};
