// Fill out your copyright notice in the Description page of Project Settings.

#include "RoadSection.h"
#include "Components/BoxComponent.h"
#include "RunnerCharacter.h"



// Sets default values
ARoadSection::ARoadSection ()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root comp", false);
	SetRootComponent(RootComponent);
	TriggerBox = CreateDefaultSubobject <UBoxComponent>("Trigger box", true);
	/*FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
	TriggerBox->AttachToComponent(RootComponent,Rules,"sdf");*/
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetRelativeLocation(FVector(0,0,0));
	TriggerBox->SetRelativeScale3D(FVector (1,1,50));
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	//TriggerBox->bHiddenInGame = false;
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ARoadSection::TriggerOverlapped);
}

// Called when the game starts or when spawned
void ARoadSection::BeginPlay()
{
	Super::BeginPlay();
	//TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ARoadSection::TriggerOverlapped);

	//FString Message = "Section start playing ";
	//Message.Append(this->GetName());
	//GEngine->AddOnScreenDebugMessage(0,2,FColor::Blue, Message);
	//bool added = TriggerBox->OnComponentBeginOverlap.IsAlreadyBound(this, &ARoadSection::TriggerOverlapped);
	//UE_LOG(LogTemp,Warning,TEXT("begin play by %s added %d"), *TriggerBox->GetName(),added);
}

// Called every frame
void ARoadSection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoadSection::TriggerOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (OtherActor->GetClass() == ARunnerCharacter::StaticClass()) {
	if (Cast<ARunnerCharacter>(OtherActor)) {
		//GEngine->AddOnScreenDebugMessage(0, 2, FColor::Purple, "Section trigger box overlapped");
		TriggerDelegateList.Broadcast();
		TriggerDelegateList.Clear();
		TriggerBox->DestroyComponent();
	}
	//else GEngine->AddOnScreenDebugMessage(0, 2, FColor::Purple, "Section overlaped by wrong actor");
}

void ARoadSection::TriggerEndOverlap(UPrimitiveComponent* OnComponentEndOverlap, UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


