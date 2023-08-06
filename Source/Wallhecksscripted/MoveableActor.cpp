// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveableActor.h"
#include "Components/TimelineComponent.h"

// Sets default values
AMoveableActor::AMoveableActor()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create the timeline component
    MovementTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("MovementTimeline"));

    // Bind the timeline functions
    MovementTimeline->AddInterpFloat(MovementCurve, FOnTimelineFloat::CreateUFunction(this, FName("TimelineCallback")));
    MovementTimeline->SetTimelineFinishedFunc(FOnTimelineEvent::CreateUFunction(this, FName("TimelineFinishedCallback")));

    // Set defaults
    MovementSpeed = 500.0f; // Change this to adjust the movement speed
}

void AMoveableActor::BeginPlay()
{
    Super::BeginPlay();
}

void AMoveableActor::TimelineCallback(float Value)
{
    // Update the actor's position during the timeline interpolation
    SetActorLocation(FMath::Lerp(TargetPoints[0], TargetPoints[1], Value));
}

void AMoveableActor::TimelineFinishedCallback()
{
    // Move to the next point when the timeline finishes
    MoveToNextPoint();
}

void AMoveableActor::MoveToNextPoint()
{
    if (TargetPoints.Num() < 2)
        return;

    // Start a new timeline to interpolate movement between points
    MovementTimeline->PlayFromStart();
}
