// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class GENERICGAME_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int AddXP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int score;
	float speed;
	bool canMove;
	FString itemDescription;
	int xp;

	void ShowLogs();
	void AddScore(int points, bool canAddBonus = false, int pointsBonus = 2);

private:	

};
