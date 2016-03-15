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

AMovingPlatform::~AMovingPlatform()
{
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// Setup Animation
	startPos = this->GetActorLocation();
	t = tStart;
	distToTarget = FVector::Dist(startPos, targetPos->GetComponentLocation());
	if(startOnOtherSide)
	{
		direction = true;
		smoothInterpolate = new SmoothInterpolate(targetPos->GetComponentLocation(), sloopDist, distToTarget, moveSpeed, sloopPower, sloopMult, t);
	}
	else
	{
		direction = false;
		smoothInterpolate = new SmoothInterpolate(startPos, sloopDist, distToTarget, moveSpeed, sloopPower, sloopMult, t);
	}
}

// Called whenever this actor is being removed from a level
void AMovingPlatform::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	delete smoothInterpolate;
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector currentPos = movingObject->GetComponentLocation();
	if (pauseTimer > 0.0f)
	{
		pauseTimer -= DeltaTime;
	}
	else
	{
		t = smoothInterpolate->UpdatePosition(currentPos, DeltaTime);
	}

	// update lerp t
	if (t > 1.0f)
	{
		pauseTimer = pauseTime;
		t = 0.0f;
		delete smoothInterpolate;
		if (direction)
		{
			direction = false;
			smoothInterpolate = new SmoothInterpolate(startPos, sloopDist, distToTarget, moveSpeed, sloopPower, sloopMult, 0.0f);
		}
		else
		{
			direction = true;
			smoothInterpolate = new SmoothInterpolate(targetPos->GetComponentLocation(), sloopDist, distToTarget, moveSpeed, sloopPower, sloopMult, 0.0f);
		}
	}

	// calculate movment
	if (direction)
	{
		newPos = MathUtil::Lerp(targetPos->GetComponentLocation(), startPos, t);
	}
	else
	{
		newPos = MathUtil::Lerp(startPos, targetPos->GetComponentLocation(), t);
	}
	time += DeltaTime;
	// move
	FHitResult* moveHitResult = new FHitResult();
	ETeleportType teleType = teleportType ? ETeleportType::TeleportPhysics : ETeleportType::None;
	movingObject->AddWorldOffset(newPos - movingObject->GetComponentLocation(), bSweep, moveHitResult, teleType);
	if (bSweep && !moveHitResult->IsValidBlockingHit())
	{
		movingObject->AddWorldOffset(newPos - movingObject->GetComponentLocation(), false, moveHitResult, teleType);
	}
	else
	{
		smoothInterpolate->SetOldInterpolation();
	}
	//UE_LOG(LogTemp, Warning, TEXT("ReceiveHit - IsValidBlockingHit: %d - time: %d"), moveHitResult->IsValidBlockingHit() , time);

	delete moveHitResult;
}

// Called on hit
void AMovingPlatform::NotifyHit(
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

	//Hit.TraceEnd
	//UE_LOG(LogTemp, Warning, TEXT("ReceiveHit - IsValidBlockingHit:%d"), Hit.IsValidBlockingHit());
}