// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadSpawner.h"

// Sets default values
ARoadSpawner::ARoadSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root",false);
	
}



// Called when the game starts or when spawned
void ARoadSpawner::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Spawning start sections . . . "));
	//for (int i = 0; i < 4; i++) { SpawnSection(); };
	SpawnSection();
	//	UE_LOG(LogTemp, Warning, TEXT("Searching for sessions complete"));
}

// Called every frame
void ARoadSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoadSpawner::RespawnRoads()
{
	for (ARoadSection* Road : RoadSections) {
		if (IsValid(Road)) 			Road->Destroy();
	}
	RoadSections.Empty();
	LastSectionIndex = 0;
	for (int i = 0; i < 4; i++) { SpawnSection(); };
}

void ARoadSpawner::SpawnSection()
{
	//GEngine->AddOnScreenDebugMessage(0,1,FColor::Orange,"Spawner producing road section . . . ");
	FActorSpawnParameters SParams;
	//SParams.pos
	float Xloc = LastSectionIndex * 1000;
	int d = rand();
	TSubclassOf<ARoadSection> RoadClass=ARoadSection::StaticClass();
	if (RoadClasses.Num() > 0)
	{
		if (!LastSectionIndex)RoadClass = FirstRoadClass;
		else RoadClass = RoadClasses[FMath::RandRange(0, RoadClasses.Num()-1)];
		//FString RoadName = RoadClass->GetName();
		//FString RoadName = "sdf";
		//UE_LOG(LogTemp, Warning, TEXT("Road class -> %s"), RoadName);
		//GEngine->AddOnScreenDebugMessage(0,24,FColor::Yellow,RoadName);
	}
	ARoadSection* SpawnedSection = GetWorld()->SpawnActor <ARoadSection>(RoadClass, FVector(0, Xloc, 0), FRotator(0, 0, 0), SParams);
	//SpawnedSection->TriggerBox->OnComponentBeginOverlap.AddDynamic(this,&ARoadSpawner::BoxCompOverlapped);
	//UE_LOG(LogTemp, Warning, TEXT("Spawned section"));
	LastSectionIndex++;
	SpawnedSection->TriggerDelegateList.AddDynamic(this, &ARoadSpawner::SpawnSection);
	RoadSections.Add(SpawnedSection);
	if (RoadSections.Num() > 7) {
		if (RoadSections.IsValidIndex(0)) {
			RoadSections[0]->Destroy();
			RoadSections.RemoveAt(0);
			//GEngine->AddOnScreenDebugMessage(0,2,FColor::Emerald,"Deleted section");
		}
	}
}

void ARoadSpawner::BoxCompOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//FString Text = "Spawner trigger overlapped by ";
	//FString Name = OtherActor->GetName();
	//Text.Append(OtherActor->GetName());
	//GEngine->AddOnScreenDebugMessage(0,2,FColor::Magenta,FString::Printf(TEXT("spawner - > section -> box overlapped by -> %s"),*OtherActor->GetName()));

}

