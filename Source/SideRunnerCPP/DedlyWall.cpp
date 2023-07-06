// Fill out your copyright notice in the Description page of Project Settings.

#include "DedlyWall.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ADedlyWall::ADedlyWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent = CreateDefaultSubobject<USceneComponent>("Root",false);
	//SetRootComponent(RootComponent);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Static mesh", false);
	SetRootComponent(Mesh);
	/*FAttachmentTransformRules Rules{
		EAttachmentRule::KeepRelative,EAttachmentRule::KeepRelative,
		EAttachmentRule::KeepRelative, false	};
	//Rules.LocationRule = EAttachmentRule::KeepWorld;
	Mesh->AttachToComponent(RootComponent,Rules);*/
	Mesh->SetEnableGravity(false);
	Mesh->SetSimulatePhysics(true);
	//Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

void ADedlyWall::WallOverlapped(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(0,1,FColor::Red,"Wall overlapped something",false);
	if (ARunnerCharacter* PlCharacter=Cast<ARunnerCharacter>(OtherActor)) {
		PlCharacter->KillCharacter();
	}
}

// Called when the game starts or when spawned
void ADedlyWall::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ADedlyWall::WallOverlapped);
	TArray <AActor*> Chars;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARunnerCharacter::StaticClass(),Chars);
	if (Chars.Num()) 	if (Chars[0]) PlayerCharacter =Cast<ARunnerCharacter>( Chars[0] );



}

// Called every frame
void ADedlyWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsValid(PlayerCharacter)) {
		float distance = this->GetActorLocation().Y - PlayerCharacter->GetActorLocation().Y;
		if (PlayerCharacter->bCanMove) {

			distance = FMath::Abs(distance);
			distance = FMath::Clamp(distance / 1.8f, 400.f, 1500.f);
			Mesh->SetPhysicsLinearVelocity(FVector(0, distance, 0));
			//GEngine->AddOnScreenDebugMessage(0, 1, FColor::Green, FString::Printf(TEXT("Wall's speed is %f"), distance));
		}
		else {
			if (distance > 3000) {
				Mesh->SetPhysicsLinearVelocity(FVector(0, 0, 0));
				//GEngine->AddOnScreenDebugMessage(0, 0, FColor::Orange, "wallStopped");
			}
			//GEngine->AddOnScreenDebugMessage(0, 0, FColor::Orange, FString::FromInt(distance));
		}
	}


}

void ADedlyWall::StartFunction()
{
	Mesh->SetPhysicsLinearVelocity(FVector(0, YSpeed, 0));
	this->SetActorLocation(FVector(0,-970,1050));
}

