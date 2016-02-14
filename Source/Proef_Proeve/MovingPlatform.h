// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MathUtil.h"
#include "MovingPlatform.generated.h"

UCLASS()
class PROEF_PROEVE_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AMovingPlatform(const FObjectInitializer& objectInitializer);
	~AMovingPlatform();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void OnHit(AActor* Other);
	virtual void PlatformBeginOverlap(AActor* Other);
	virtual void PlatformEndOverlap(AActor* Other);

	UPROPERTY(EditAnywhere, Category = Movement)
		float moveSpeed = 5.0f;

	UPROPERTY(EditAnywhere, Category = Movement)
		float tStart = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = Movement)
		USceneComponent *platformRoot;

	UPROPERTY(VisibleAnywhere, Category = Movement)
		USceneComponent *targetPos;

	UPROPERTY(EditAnywhere, Category = Movement)
		UStaticMeshComponent *movingObject;

private:
	// Amimation variables
	SmoothInterpolate *smoothInterpolate;

	UPROPERTY(EditAnywhere, Category = Movement)
		float sloopDist = 50.0f;
	UPROPERTY(EditAnywhere, Category = Movement)
		float sloopPower = 10.0f;
	UPROPERTY(EditAnywhere, Category = Movement)
		float sloopMult = 10.0f;
	UPROPERTY(EditAnywhere, Category = Movement)
		float pauseTime = 2.0f;
	UPROPERTY(EditAnywhere, Category = Movement)
		bool bSweep = false;

	UPROPERTY(VisibleAnywhere, Category = Debug)
		float  pauseTimer = 0.0f;
	UPROPERTY(VisibleAnywhere, Category = Debug)
		float t;
	UPROPERTY(VisibleAnywhere, Category = Debug)
		FVector startPos;
	UPROPERTY(VisibleAnywhere, Category = Debug)
		FVector newPos;
	UPROPERTY(VisibleAnywhere, Category = Debug)
		bool direction;
	UPROPERTY(VisibleAnywhere, Category = Debug)
		float distToTarget;

	// collision variables
	//UActorComponent* platformCollider;
};
