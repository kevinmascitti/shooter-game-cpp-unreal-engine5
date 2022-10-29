// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterGameMode.h"
#include "EnemyController.h"
#include "GameWidget.h"

ASpaceShooterGameMode::ASpaceShooterGameMode()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASpaceShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
	((UGameWidget*)CurrentWidget)->Load();
}

void ASpaceShooterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	gameTimer+=DeltaTime;
	enemyTimer-=DeltaTime;

	// UE_LOG(LogTemp, Warning, TEXT("Timer is %f"), enemyTimer);
	if(enemyTimer<=0.0f)
	{
		float difficultyPercentage = FMath::Min(gameTimer/TIME_TO_MINIMUM_INTERVAL, 1.0f);
		enemyTimer = MAXIMUM_INTERVAL - (MAXIMUM_INTERVAL-MINIMUM_INTERVAL) * difficultyPercentage;

		UE_LOG(LogTemp, Warning, TEXT("Timer is %f"), enemyTimer);

		UWorld* world = GetWorld();
		if(world)
		{
			FVector location = FVector(800.0f, FMath::RandRange(-SpawnLocationEnemyMax, SpawnLocationEnemyMax), 70.0f);
			world->SpawnActor<AEnemyController>(EnemyBlueprint, location, FRotator::ZeroRotator);
		}
	}
}

void ASpaceShooterGameMode::IncrementScore()
{
	score+=100;
	((UGameWidget*) CurrentWidget)->SetScore(score);
}

void ASpaceShooterGameMode::OnGameOver()
{
	((UGameWidget*) CurrentWidget)->OnGameOver(score);
}

void ASpaceShooterGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if(CurrentWidget!=nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if(NewWidgetClass!=nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(),NewWidgetClass);
		if(CurrentWidget!=nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
