// Fill out your copyright notice in the Description page of Project Settings.

#include "Spike.h"
#include "RunnerCharacter.h"


// Sets default values
ASpike::ASpike()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject <UStaticMeshComponent>("Spike self", false);
	SetRootComponent(Mesh);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}

void ASpike::SpikeOverapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Spike Ovelapped"));
	if (IsValid(OtherActor)) {
	ARunnerCharacter* PlayerCharacter = Cast<ARunnerCharacter>(OtherActor);
	if (IsValid(PlayerCharacter)) PlayerCharacter->KillCharacter();		
	}
}

// Called when the game starts or when spawned
void ASpike::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ASpike::SpikeOverapped);
	
}

// Called every frame
void ASpike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

