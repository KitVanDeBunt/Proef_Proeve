// Fill out your copyright notice in the Description page of Project Settings.

#include "Proef_Proeve.h"
#include "MyTestActor.h"

// Sets default values
AMyTestActor::AMyTestActor(const FObjectInitializer& objectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = objectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Box"));
}

// Called when the game starts or when spawned
void AMyTestActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyTestActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// move
	box->AddWorldOffset(speed, bSweep);
}

// Called on hit
void AMyTestActor::NotifyHit(
	class UPrimitiveComponent* MyComp,
	AActor* Other,
	class UPrimitiveComponent* OtherComp,
	bool bSelfMoved,
	FVector HitLocation,
	FVector HitNormal,
	FVector NormalImpulse,
	const FHitResult& Hit) 
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);


	//UE_LOG(LogTemp, Warning, TEXT("ReceiveHit"));
}

