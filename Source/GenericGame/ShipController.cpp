// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipController.h"
#include "Components/BoxComponent.h"
#include "BulletController.h"
#include "EnemyController.h"
#include "SAdvancedTransformInputBox.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceShooterGameMode.h"

// Sets default values
AShipController::AShipController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	collisionBox->SetGenerateOverlapEvents(true);
	collisionBox->OnComponentBeginOverlap.AddDynamic(this, &AShipController::OnTriggerEnter);
	
	// Set the player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
}

// Called when the game starts or when spawned
void AShipController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShipController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!currentVelocity.IsZero())
	{
		FVector newLocation = GetActorLocation() + (speed * currentVelocity * DeltaTime);
		
		if(newLocation.X<-SpawnLocationMax) newLocation.X = -SpawnLocationMax;
		else if(newLocation.X>SpawnLocationMax) newLocation.X = SpawnLocationMax;
		if(newLocation.Y<-(SpawnLocationMax*2)) newLocation.Y = -(SpawnLocationMax*2);
		else if(newLocation.Y>(SpawnLocationMax*2)) newLocation.Y = SpawnLocationMax*2;
		
		SetActorLocation(newLocation);
	}

}

// Called to bind functionality to input
void AShipController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, &AShipController::MoveXAxis);
	InputComponent->BindAxis("MoveY", this, &AShipController::MoveYAxis);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &AShipController::OnShoot);
	InputComponent->BindAction("Restart", IE_Pressed, this, &AShipController::OnRestart).bExecuteWhenPaused=true;

}

void AShipController::MoveXAxis(float AxisValue)
{
	currentVelocity.X = AxisValue * 100.0f;
}

void AShipController::MoveYAxis(float AxisValue)
{
	currentVelocity.Y = AxisValue * 100.0f;
}

void AShipController::OnShoot()
{
	UWorld* world = GetWorld();
	if(world)
	{
		FVector location = GetActorLocation();
		world->SpawnActor<ABulletController>(BulletBP, FVector(location.X + SpawnDistanceValue, location.Y, location.Z), FRotator::ZeroRotator);
	}
}

void AShipController::OnRestart()
{
	if(Died)
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName(), false));
	}
}


void AShipController::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// UE_LOG(LogTemp, Warning, TEXT("TRIGGER"));
	if(OtherActor->IsA(AEnemyController::StaticClass()))
	{
		// UE_LOG(LogTemp, Warning, TEXT("TRIGGER WITH ENEMY"));
		Died = true;
		this->SetActorHiddenInGame(true);
		
		((ASpaceShooterGameMode*) GetWorld()->GetAuthGameMode())->OnGameOver();

		// The game is paused
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

