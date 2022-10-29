// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShipController.generated.h"

UCLASS()
class GENERICGAME_API AShipController : public APawn
{
	GENERATED_BODY()

	public:
	// Sets default values for this pawn's properties
	AShipController();

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere)
	UShapeComponent* collisionBox;

	UPROPERTY(EditAnywhere)
	float speed = 10.0f;

	UPROPERTY(EditAnywhere)
	float SpawnLocationMax = 400.0f;

	UPROPERTY(EditAnywhere)
	float SpawnDistanceValue = 50.0f;

	UPROPERTY(EditAnywhere, Category="Spawning")
	TSubclassOf<class ABulletController> BulletBP;
	
	void MoveXAxis(float AxisValue);
	void MoveYAxis(float AxisValue);
	void OnShoot();
	void OnRestart();
	
	FVector currentVelocity;

	bool Died;

	UFUNCTION()
	void OnTriggerEnter(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
