// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class PROEF_PROEVE_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AMovingPlatform(const FObjectInitializer& objectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		float moveSpeed = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		float tStart = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		USceneComponent *targetPos;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		USceneComponent *movingObject;

private:
	float t;
	FVector startPos;
	FVector newPos;
	bool direction;
};
