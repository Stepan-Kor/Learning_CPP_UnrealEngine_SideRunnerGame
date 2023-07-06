// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "RoadSpawner.h"
#include "Components/BoxComponent.h"
#include "RoadSection.generated.h"


//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FoodEatenEvent, FString, Food_Type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerDelegateSignature);
UCLASS()
class SIDERUNNERCPP_API ARoadSection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoadSection();
	UPROPERTY ( BlueprintReadWrite) UBoxComponent* TriggerBox;
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FTriggerDelegateSignature TriggerDelegateList;
	USceneComponent* Root;
	//ARoadSpawner* Spawner;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
//UPROPERTY(VisibleAnywhere)  RoadSpawner* Spawner;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION (BlueprintCallable) void TriggerOverlapped(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION (BlueprintCallable) void TriggerEndOverlap(UPrimitiveComponent* OnComponentEndOverlap,
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
