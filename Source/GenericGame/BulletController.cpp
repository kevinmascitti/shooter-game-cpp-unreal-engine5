// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletController.h"
#include "EnemyController.h"
#include "Components/BoxComponent.h"
#include "SpaceShooterGameMode.h"

// Sets default values
ABulletController::ABulletController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ROOT"));
	rootBox->SetGenerateOverlapEvents(true);
	rootBox->OnComponentBeginOverlap.AddDynamic(this, &ABulletController::OnOverlap);
}

// Called when the game starts or when spawned
void ABulletController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move bullet
	FVector newLocation = GetActorLocation();
	newLocation.X += speed*DeltaTime;
	SetActorLocation(newLocation);
	// UE_LOG(LogTemp, Warning, TEXT("Bullet location: %f"), newLocation.X);

	// Destroy bullet
	if(newLocation.X > 2500.0f)
	{
		this->Destroy();
	}
}

void ABulletController::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// UE_LOG(LogTemp, Warning, TEXT("TRIGGER"));
	if(OtherActor->IsA(AEnemyController::StaticClass()))
	{
		this->Destroy();
		OtherActor->Destroy();
		
		((ASpaceShooterGameMode*) GetWorld()->GetAuthGameMode())->IncrementScore();
	}
}