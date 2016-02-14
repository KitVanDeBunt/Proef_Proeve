// Fill out your copyright notice in the Description page of Project Settings.

#include "Proef_Proeve.h"
#include "MovingPlatform.h"


// Sets default values
AMovingPlatform::AMovingPlatform(const FObjectInitializer& objectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	direction = true;
	// create root
	platformRoot = objectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = platformRoot;
	// create target
	targetPos = objectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Movment Target"));
	targetPos->AttachTo(platformRoot);
	// create platform
	movingObject = objectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Platform"));
}

AMovingPlatform::~AMovingPlatform(){
	delete smoothInterpolate;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// Setup Animation
	startPos = this->GetActorLocation();
	t = tStart;
	distToTarget = FVector::Dist(startPos, targetPos->GetComponentLocation());
	smoothInterpolate = new SmoothInterpolate(startPos, sloopDist, distToTarget, moveSpeed, sloopPower, sloopMult);

	// Setup collision
	//movingObject->OnComponentHit.AddDynamic(this, &AMovingPlatform::OnHit);
	//OnActorBeginOverlap.AddDynamic(this, &AMovingPlatform::PlatformBeginOverlap);
	//OnActorEndOverlap.AddDynamic(this, &AMovingPlatform::PlatformEndOverlap);

}

void AMovingPlatform::OnHit(AActor* Other){
	UE_LOG(LogTemp, Warning, TEXT("OnHit"));
}
void AMovingPlatform::PlatformBeginOverlap(AActor* Other){
	UE_LOG(LogTemp, Warning, TEXT("BeginOverlap"));
}
void AMovingPlatform::PlatformEndOverlap(AActor* Other){
	UE_LOG(LogTemp, Warning, TEXT("EndOverlap"));
}

// Called every frame
void AMovingPlatform::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector currentPos = movingObject->GetComponentLocation();
	if (pauseTimer > 0.0f){
		pauseTimer -= DeltaTime;
	}else{
		t = smoothInterpolate->UpdatePosition(currentPos, DeltaTime);
	}

	// update lerp t
	if (t > 1.0f) {
		pauseTimer = pauseTime;
		t = 0.0f;
		delete smoothInterpolate;
		if (direction) {
			direction = false;
			smoothInterpolate = new SmoothInterpolate(startPos, sloopDist, distToTarget, moveSpeed, sloopPower, sloopMult);
		}else {
			direction = true;
			smoothInterpolate = new SmoothInterpolate(targetPos->GetComponentLocation(), sloopDist, distToTarget, moveSpeed, sloopPower, sloopMult);
		}
	}
	// calculate movment
	if (direction) {
		newPos = MathUtil::Lerp(targetPos->GetComponentLocation(), startPos, t);
	}else{
		newPos = MathUtil::Lerp(startPos, targetPos->GetComponentLocation(), t);
	}
	
	// move
	movingObject->AddWorldOffset(newPos-movingObject->GetComponentLocation(), bSweep);

}

