// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveableActor.h"
#include "Components/TimelineComponent.h"

// Sets default values
AMoveableActor::AMoveableActor()
{
    PrimaryActorTick.bCanEverTick = true;

    MovementTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("MovementTimeline"));
    MovementTimeline->SetLooping(false);
    MovementTimeline->SetIgnoreTimeDilation(true);

    MovementSpeed = 500.0f;

    static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/Path/To/Your/Curve.FloatCurve'"));
    MovementCurve = Curve.Object;

    // Bind the timeline functions
    FOnTimelineFloat TimelineCallback;
    TimelineCallback.BindUFunction(this, FName("OnTimelineCallback"));
    MovementTimeline->AddInterpFloat(MovementCurve, TimelineCallback);

    FOnTimelineEvent TimelineFinishedCallback;
    TimelineFinishedCallback.BindUFunction(this, FName("OnTimelineFinishedCallback"));
    MovementTimeline->SetTimelineFinishedFunc(TimelineFinishedCallback);
}

void AMoveableActor::BeginPlay()
{
    Super::BeginPlay();
}

void AMoveableActor::SetTargetPoints(const TArray<FVector>& NewTargetPoints)
{
    TargetPoints = NewTargetPoints;
}

void AMoveableActor::OnTimelineCallback(float Value)
{
    // Update the actor's position during the timeline interpolation
    SetActorLocation(FMath::Lerp(TargetPoints[0], TargetPoints[1], Value));
}

void AMoveableActor::OnTimelineFinishedCallback()
{
    // Move to the next point when the timeline finishes
    MoveToNextPoint();
}

void AMoveableActor::MoveToNextPoint()
{
    if (TargetPoints.Num() < 2)
        return;

    // If the timeline is already playing, stop it
    if (MovementTimeline->IsPlaying())
    {
        MovementTimeline->Stop();
    }

    // Clear existing delegates and bindings
    MovementTimeline->OnTimelineFloat.RemoveAll(this);

    // Create a new timeline for the next set of target points
    MovementTimeline = NewObject<UTimelineComponent>(this, UTimelineComponent::StaticClass());
    MovementTimeline->RegisterComponent();
    MovementTimeline->SetLooping(false);
    MovementTimeline->SetIgnoreTimeDilation(true);

    // Bind the timeline functions for the new timeline
    FOnTimelineFloat TimelineCallback;
    TimelineCallback.BindUFunction(this, FName("OnTimelineCallback"));
    MovementTimeline->AddInterpFloat(MovementCurve, TimelineCallback);

    FOnTimelineEvent TimelineFinishedCallback;
    TimelineFinishedCallback.BindUFunction(this, FName("OnTimelineFinishedCallback"));
    MovementTimeline->SetTimelineFinishedFunc(TimelineFinishedCallback);

    // Update the timeline's movement points for the new target points
    for (int32 i = 0; i < TargetPoints.Num() - 1; i++)
    {
        MovementTimeline->AddInterpVector(TargetPoints[i], TargetPoints[i + 1], true);
    }

    // Start the new timeline to interpolate movement between points
    MovementTimeline->PlayFromStart();
}