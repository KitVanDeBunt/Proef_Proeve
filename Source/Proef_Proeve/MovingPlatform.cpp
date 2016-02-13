// Fill out your copyright notice in the Description page of Project Settings.

#include "Proef_Proeve.h"
#include "MovingPlatform.h"
#include "MathUtil.h"


// Sets default values
AMovingPlatform::AMovingPlatform(const FObjectInitializer& objectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	direction = true;
	targetPos = objectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Movment Target"));
	movingObject = objectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Movment Platform"));
	USceneComponent *root = objectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = root;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	startPos = this->GetActorLocation();
	t = tStart;
}

// Called every frame
void AMovingPlatform::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	// update lerp t
	if (direction) {
		t += DeltaTime*moveSpeed;
		if (t > 1.0f) {
			direction = false;
			t = 1.0f;
		}
	} else {
		t -= DeltaTime*moveSpeed;
		if (t < 0.0f) {
			direction = true;
			t = 0.0f;
		}
	}
	// calculate movment
	newPos = MathUtil::Lerp(startPos, startPos + targetPos->RelativeLocation, t);
	// move
	movingObject->SetWorldLocation(newPos, true);
}

