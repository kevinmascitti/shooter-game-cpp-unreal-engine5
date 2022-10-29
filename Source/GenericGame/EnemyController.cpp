// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

#include "Components/BoxComponent.h"

// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newLocation = GetActorLocation();
	newLocation.X += speed*DeltaTime;
	SetActorLocation(newLocation);

	if(newLocation.X < -1000.0f)
		this->Destroy();

}

