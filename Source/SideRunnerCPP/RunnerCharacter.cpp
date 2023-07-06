// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerCharacter.h"
//#include "RunnerWidget.h"
#include "RunnerGameState.h"
#include "RunnerWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ARunnerCharacter::ARunnerCharacter()
{
	GetCapsuleComponent()->SetCapsuleSize(42.f,96.f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1,ECR_Overlap);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	SideCamera = CreateDefaultSubobject <UCameraComponent>(TEXT ("Side Camera"));
	SideCamera->bUsePawnControlRotation = false;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0,720,0);
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.8f;
	GetCharacterMovement()->JumpZVelocity = 1000;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600;
	GetCharacterMovement()->MaxFlySpeed = 600;
	tempPos = GetActorLocation();
	zPosition = tempPos.Z + 300;
}

// Called when the game starts or when spawned
void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//UUserWidget* TempWidget;
	//TempWidget = Cast <ARunnerGameState> (GetWorld()->GetGameState())->MainWidget;
	MainWidget = Cast <ARunnerGameState>(GetWorld()->GetGameState())->GetMainWidget();
	if (!IsValid(MainWidget)) { UE_LOG(LogTemp, Warning, TEXT("Character DIDNT GET POINTER TO WIDGET")); }
	else { UE_LOG(LogTemp, Warning, TEXT("Character get pointer to widget")); }
	SKMesh = GetMesh();
	//GetCapsuleComponent()->bHiddenInGame = false;
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ARunnerCharacter::DelayedFunction,1,true);
}

void ARunnerCharacter::KillCharacter()
{
	if (!bCanMove) return;
	UE_LOG(LogTemp, Warning, TEXT("Character died"));
		bCanMove = false;
		if (SKMesh) {
			SKMesh->SetSimulatePhysics(true);
			SKMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		}
		if (IsValid(MainWidget)) {
			//MainWidget->ShowRestartMenu();
			//FTimerHandle UnusedHandle;			
			//GetWorldTimerManager().SetTimer(UnusedHandle, MainWidget, &URunnerWidget::ShowRestartMenu, 1, false);
			MainWidget->ShowRestartMenu();
			UE_LOG(LogTemp, Warning, TEXT("Character order to show menu to widget"));
		}
		else UE_LOG(LogTemp,Warning,TEXT("Character dont have main widget pointer"));
}

void ARunnerCharacter::DelayedFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("Cheker function . . . "));
	if (!IsValid(MainWidget))UE_LOG(LogTemp,Warning,TEXT("Character have empty pointer to widget"));
}

// Called every frame
void ARunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	tempPos = GetActorLocation();
	tempPos.Z = zPosition;
	tempPos.X -= 850.f;
	SideCamera->SetWorldLocation(tempPos);

}

void ARunnerCharacter::MoveRight(float AxisValue)
{
	if (bCanMove)AddMovementInput(FVector (0,1,0),AxisValue);
}

void ARunnerCharacter::StartFunction()
{
	SKMesh->SetSimulatePhysics(false);
	SKMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	this->SetActorLocation(FVector(0, 0, 148.15f));
	/*FAttachmentTransformRules Rules(
		EAttachmentRule::KeepRelative,
	);*/
	SKMesh->AttachToComponent(GetCapsuleComponent(),FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SKMesh->SetRelativeLocation(FVector(0, 0, -96),false);
	SKMesh->SetRelativeRotation(FRotator (0,-90,0),false);
	bCanMove = true;
}

// Called to bind functionality to input
void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight",this,&ARunnerCharacter::MoveRight);
}

