// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RunnerWidget.h"
#include "RunnerGameState.generated.h"

/**
 * 
 */
UCLASS()
class SIDERUNNERCPP_API ARunnerGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	ARunnerGameState();
		//virtual void HandleBeginPlay() override;

	UFUNCTION()	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly) TSubclassOf <UUserWidget> WidgetClass ;
	UPROPERTY(VisibleAnywhere) URunnerWidget* MainWidget;
	URunnerWidget* GetMainWidget();
};
