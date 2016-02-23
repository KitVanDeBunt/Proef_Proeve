// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnPointManager.generated.h"

UCLASS()
class PROEF_PROEVE_API ASpawnPointManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPointManager(const FObjectInitializer& objectInitializer);

	~ASpawnPointManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
private:
	UPROPERTY(EditAnywhere)
	int64 currentSpawnPointCount;

	UPROPERTY(EditAnyWhere)
	TArray<UBoxComponent*> spawn;
};
