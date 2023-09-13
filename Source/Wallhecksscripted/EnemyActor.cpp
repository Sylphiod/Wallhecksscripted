// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
	MySphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MySphereComponent->InitSphereRadius(100.f);
	MySphereComponent->SetCollisionProfileName(TEXT("Trigger"));
	RootComponent = MySphereComponent;

	MySphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnOverlapBegin);
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Initialize default values
	RestTimeBetweenMovements = 2.0f;
	MovementSpeed = 500.0f;
	CurrentRestTime = 0.0f;
	CurrentPointIndex = 0;
}

void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Save the initial location of the actor
	InitialLocation = GetActorLocation();
}

void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if there are movement points defined
	if (MovementPoints.Num() == 0)
		return;

	// Calculate the movement direction and distance
	FVector CurrentTargetPoint = MovementPoints[CurrentPointIndex];
	FVector Direction = CurrentTargetPoint - GetActorLocation();
	float DistanceToTarget = Direction.Size();

	// Move the actor towards the target point
	if (DistanceToTarget > 20.0f)
	{
		Direction.Normalize();
		FVector NewLocation = GetActorLocation() + Direction * MovementSpeed * DeltaTime;
		SetActorLocation(NewLocation);
	}
	else
	{
		// If the actor reached the target point, rest for a while
		CurrentRestTime += DeltaTime;
		if (CurrentRestTime >= RestTimeBetweenMovements)
		{
			// Move to the next point and reset rest time
			CurrentPointIndex = (CurrentPointIndex + 1) % MovementPoints.Num();
			CurrentRestTime = 0.0f;
		}
	}
}

void AEnemyActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();
}

