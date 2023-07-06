// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "RunnerCharacter.h"
#include "RunnerSaveGame.h"
#include "DedlyWall.h"
#include "RoadSpawner.h"
#include "RunnerWidget.generated.h"


/**
 * 
 */
UCLASS(meta=(EnableNativeTick))
class SIDERUNNERCPP_API URunnerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
		UPROPERTY(meta=(BindWidget)) UButton* StartButton;
		UPROPERTY(meta=(BindWidget)) UButton* ExitButton;
		UPROPERTY(meta=(BindWidget)) UVerticalBox* VerticalBoxMain;
		UPROPERTY(meta = (BindWidget)) UTextBlock* TextBlock_MaxPoints;
		UPROPERTY(meta = (BindWidget)) UTextBlock* TextBlock_CurrentPoints;
		UPROPERTY(meta = (BindWidget)) UButton* ResetButton;
		virtual bool Initialize() override;
		UFUNCTION() void ExitFunction();
		UFUNCTION() void StartGameFunction();
		UFUNCTION() void ResetMaxPoints();
		void ShowRestartMenu();
		void UpdateRecordPoints(int32 Points);
		virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
		bool bGameStarted=false;
		ARunnerCharacter* PlChar;
		ADedlyWall* Wall;
		APlayerController* PlController;
		ARoadSpawner* RoadSpawner;
		UPROPERTY (VisibleAnywhere)URunnerSaveGame* SaveFile;
		const FString SlotName = "Save file";
		int32 CurrentPoints;

};

