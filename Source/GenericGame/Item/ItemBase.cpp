// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

// Sets default values
AItemBase::AItemBase():
	score(0),
	speed(4.55f),
	canMove(false),
	itemDescription("This is the item"),
	xp(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	ShowLogs();
	AddScore(1);
	ShowLogs();
	AddScore(1,true, 12);
	ShowLogs();
	AddScore(1, true);
	ShowLogs();
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// actor si muove

}

// ----------------------------------------------------------------

void AItemBase::ShowLogs()
{
	UE_LOG(LogTemp, Warning, TEXT("*** Logs for the Game ***"), score);
	UE_LOG(LogTemp, Warning, TEXT("Score: %d"), score);
	UE_LOG(LogTemp, Warning, TEXT("Speed: %f"), speed);
	UE_LOG(LogTemp, Warning, TEXT("canMove: %d"), canMove);
	UE_LOG(LogTemp, Warning, TEXT("itemDescription: %s"), *itemDescription);
	UE_LOG(LogTemp, Warning, TEXT("XP = %d"), xp);
}

void AItemBase::AddScore(int points, bool canAddBonus, int pointsBonus)
{
	if(canAddBonus == true && score >10)
		score += points+pointsBonus+2;
	else if(canAddBonus==true && score <10)
	{
		score += points+pointsBonus;
	}
	else
	{
		score += points;
	}
}

int AItemBase::AddXP()
{
	xp = score * 2;
	return xp;
}
