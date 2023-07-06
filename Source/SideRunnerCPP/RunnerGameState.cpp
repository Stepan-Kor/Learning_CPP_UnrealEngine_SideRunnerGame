// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerGameState.h"


ARunnerGameState::ARunnerGameState()
{
	WidgetClass = URunnerWidget::StaticClass();
}

void ARunnerGameState::BeginPlay()
{
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(0, 12, FColor::Red, "Game state start playing.");
	//UE_LOG (LogTemp,Warning,TEXT("Game state started playing."));
	//MainWidget = Cast <URunnerWidget>(CreateWidget(GetWorld(), WidgetClass));
	//MainWidget->AddToViewport();
	GetMainWidget();
}

URunnerWidget* ARunnerGameState::GetMainWidget()
{
	if (IsValid(MainWidget)) return MainWidget;
	else {
		MainWidget = Cast <URunnerWidget>(CreateWidget(GetWorld(), WidgetClass));
		MainWidget->AddToViewport();
		return MainWidget;
	}
}
