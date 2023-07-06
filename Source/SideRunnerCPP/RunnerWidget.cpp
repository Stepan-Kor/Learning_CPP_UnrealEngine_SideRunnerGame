// Fill out your copyright notice in the Description page of Project Settings.

#include "RunnerWidget.h"
#include "Kismet/GameplayStatics.h"


				//virtual bool Initialize();
bool URunnerWidget::Initialize() {
	Super::Initialize();
	if (IsValid(ExitButton))ExitButton->OnClicked.AddDynamic(this, &URunnerWidget::ExitFunction);
	if (IsValid(StartButton))StartButton->OnClicked.AddDynamic(this, &URunnerWidget::StartGameFunction);
	if (IsValid(ResetButton))ResetButton->OnClicked.AddDynamic(this, &URunnerWidget::ResetMaxPoints);
	else UE_LOG(LogTemp, Warning, TEXT("ExitButton is not valid"));
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(Controller)) {
		Controller->SetInputMode(FInputModeUIOnly());
		Controller->bShowMouseCursor = true;
	}
	else GEngine->AddOnScreenDebugMessage(0, 1, FColor::Emerald, "no controller found by widget");
	AActor* Actor =	UGameplayStatics::GetActorOfClass(GetWorld(), ARunnerCharacter::StaticClass());
	PlChar = Cast<ARunnerCharacter>(Actor);
	if (IsValid(PlChar)) PlController = Cast <APlayerController>(PlChar->GetController());
	Actor = UGameplayStatics::GetActorOfClass(GetWorld(),ADedlyWall::StaticClass());
	Wall = Cast <ADedlyWall>(Actor);
	Actor = UGameplayStatics::GetActorOfClass(GetWorld(),ARoadSpawner::StaticClass());
	RoadSpawner = Cast<ARoadSpawner>(Actor);
	SaveFile = Cast <URunnerSaveGame>(UGameplayStatics::LoadGameFromSlot (SlotName, 0));
	//GEngine->AddOnScreenDebugMessage(0, 2, FColor::Emerald, "151515",false);
	
	if (IsValid(SaveFile)) { 
		UE_LOG(LogTemp, Warning, TEXT("SaveFile loaded %i"),SaveFile->MaxPoints);
		//GEngine->AddOnScreenDebugMessage(0, 2, FColor::Emerald, "Save data loaded", false); 
	}
	else{
		SaveFile = Cast <URunnerSaveGame>(UGameplayStatics::CreateSaveGameObject(URunnerSaveGame::StaticClass()));
		UGameplayStatics::SaveGameToSlot(SaveFile, SlotName, 0);
		//GEngine->AddOnScreenDebugMessage(0, 2, FColor::Emerald, "Save data created",false);
		UE_LOG(LogTemp, Warning, TEXT("SaveFile created"));
	}
			
	if (SaveFile && TextBlock_MaxPoints) { 
		TextBlock_MaxPoints->SetText(FText::FromString(FString::FromInt(SaveFile->MaxPoints))); 
		//GEngine->AddOnScreenDebugMessage(0,3,FColor::Emerald,FString::Printf(TEXT("TextBlock Updated %i"),SaveFile->MaxPoints));
	}
	//this->bCanEverTick
	return true;
}

void URunnerWidget::ExitFunction()
{
	UE_LOG (LogTemp,Warning,TEXT("ExitButton"));
	UKismetSystemLibrary::QuitGame(GetWorld(),UGameplayStatics::GetPlayerController(GetWorld(),0), EQuitPreference::Quit,true);
}

void URunnerWidget::StartGameFunction()
{
	if (IsValid(PlChar))PlChar->StartFunction();
	if (IsValid(Wall))Wall->StartFunction();
	RoadSpawner->RespawnRoads();
	//APlayerController* Conroller UGameplayStatics::GetPlayerController(GetWorld(), 0)->;
	if (PlController) {
		PlController->SetInputMode(FInputModeGameOnly());
		PlController->bShowMouseCursor = false;
		VerticalBoxMain->SetVisibility(ESlateVisibility::Hidden);
	}
	CurrentPoints = 0;
	TextBlock_CurrentPoints->SetText(FText::FromString("0"));
}

void URunnerWidget::ResetMaxPoints()
{

		if (IsValid(SaveFile))SaveFile->MaxPoints = 0;
		else UE_LOG(LogTemp, Warning, TEXT("resetmax points - save file not valid"));
		
		if(IsValid(SaveFile))		UGameplayStatics::SaveGameToSlot(SaveFile, SlotName, 0);
		else UE_LOG(LogTemp, Warning, TEXT("resetmax points - save file not valid"));
		if(IsValid(TextBlock_MaxPoints))TextBlock_MaxPoints->SetText(FText::FromString("0"));
		else UE_LOG(LogTemp, Warning, TEXT("resetmax points - textblock not valid"));
		
}

void URunnerWidget::ShowRestartMenu()
{
	if (IsValid(PlController) && IsValid(VerticalBoxMain) && IsValid(TextBlock_CurrentPoints)) {
		bGameStarted = false;
		VerticalBoxMain->SetVisibility(ESlateVisibility::Visible);
		PlController->bShowMouseCursor = true;
		PlController->SetInputMode(FInputModeUIOnly());
		UpdateRecordPoints(CurrentPoints);
		//CurrentPoints = 0;
		//TextBlock_CurrentPoints->SetText(FText::FromString("0"));
	}
	else UE_LOG(LogTemp,Warning,TEXT("Cant show menu - something is not valid !  !  !"));
}

void URunnerWidget::UpdateRecordPoints(int32 Points)
{
	if (IsValid(SaveFile)) {
		if (SaveFile->MaxPoints < Points) {
			SaveFile->MaxPoints = Points;
			if (!IsValid(SaveFile)) UE_LOG(LogTemp, Warning, TEXT("Cant update record points - SaveFile is not valid"));
			bool Suc = UGameplayStatics::SaveGameToSlot(SaveFile, SlotName, 0);
			if (Suc)GEngine->AddOnScreenDebugMessage(0, 7, FColor::Emerald, FString::Printf(TEXT("Points updated %i"), Points));
			else GEngine->AddOnScreenDebugMessage(0, 7, FColor::Emerald, FString::Printf(TEXT("Points not updated %i"), Points));
			if (IsValid(TextBlock_MaxPoints))		TextBlock_MaxPoints->SetText(FText::FromString(FString::FromInt(Points)));
		}
	}
	else UE_LOG(LogTemp, Warning, TEXT("Cant update record points no savefile"));
	
}

void URunnerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	//GEngine->AddOnScreenDebugMessage(0, 1, FColor::Emerald,"Tick func");
	if (IsValid(PlChar)) {
		if (PlChar->bCanMove) {
			int32 TempInt = PlChar->GetActorLocation().Y;
			if (TempInt > CurrentPoints) {
				CurrentPoints = TempInt;
				TextBlock_CurrentPoints->SetText(FText::FromString(FString::FromInt(TempInt)));
			}
		}
	}
}
