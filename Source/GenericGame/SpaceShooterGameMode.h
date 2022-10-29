// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GENERICGAME_API ASpaceShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

	float MINIMUM_INTERVAL = 0.5f;
	float MAXIMUM_INTERVAL = 2.0f;
	float TIME_TO_MINIMUM_INTERVAL = 30.0f;

	public:
	// Sets default values for this pawn's properties
	ASpaceShooterGameMode();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void IncrementScore();
	void OnGameOver();

	UPROPERTY(EditAnywhere, Category="Spawning")
	TSubclassOf<class AEnemyController> EnemyBlueprint;
	
	UPROPERTY(EditAnywhere)
	float SpawnLocationEnemyMax = 400.0f;

	float enemyTimer;
	float gameTimer;

	UFUNCTION(BlueprintCallable, Category="UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	
	protected:
	int score=0;

	UPROPERTY(EditAnywhere, Category="UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget; 
	
};
