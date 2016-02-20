// Fill out your copyright notice in the Description page of Project Settings.

#include "Proef_Proeve.h"
#include "MyTestTrigger.h"


// Sets default values
AMyTestTrigger::AMyTestTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyTestTrigger::BeginPlay()
{
	Super::BeginPlay();

	//GetWorld()->SpawnActor(triggerv::StaticClass());
}

// Called every frame
void AMyTestTrigger::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}