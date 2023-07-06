// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RunnerCharacter.generated.h"
UCLASS()
class SIDERUNNERCPP_API ARunnerCharacter : public ACharacter
{
	GENERATED_BODY()
		UPROPERTY(VisibleAnywhere) class UCameraComponent* SideCamera;

public:
	// Sets default values for this character's properties
	ARunnerCharacter();
	UFUNCTION(BlueprintCallable)void KillCharacter();
	UPROPERTY (BlueprintReadOnly)bool bCanMove = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector tempPos;
	float zPosition;
	UPROPERTY (VisibleAnywhere) class URunnerWidget* MainWidget;
	USkeletalMeshComponent* SKMesh;
	void DelayedFunction();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void StartFunction();
	
	void MoveRight(float AxisValue);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
