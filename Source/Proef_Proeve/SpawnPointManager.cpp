// Fill out your copyright notice in the Description page of Project Settings.

#include "Proef_Proeve.h"
#include "SpawnPointManager.h"


// Sets default values
ASpawnPointManager::ASpawnPointManager(const FObjectInitializer& objectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create spawn points
	for (int i = 0; i < currentSpawnPointCount; i++)
	{
		spawn.Add(objectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("Box")));
	}
	UE_LOG(LogTemp, Warning, TEXT("spawn count: %d"), spawn.Num());
}

ASpawnPointManager::~ASpawnPointManager()
{
}

// Called when the game starts or when spawned
void ASpawnPointManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnPointManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

