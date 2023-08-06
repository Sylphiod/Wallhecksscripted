// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveableActor.generated.h"

UCLASS()
class WALLHECKSSCRIPTED_API AMoveableActor : public AActor
{
    GENERATED_BODY()

public:
    AMoveableActor();

protected:
    UPROPERTY(EditAnywhere, Category = "Movement")
    TArray<FVector> TargetPoints;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float MovementSpeed;

    UPROPERTY()
    class UTimelineComponent* MovementTimeline;

    UPROPERTY()
    class UCurveFloat* MovementCurve;

    UFUNCTION()
    void OnTimelineCallback(float Value);

    UFUNCTION()
    void OnTimelineFinishedCallback();

public:
    UFUNCTION(BlueprintCallable)
    void SetTargetPoints(const TArray<FVector>& NewTargetPoints);

    UFUNCTION(BlueprintCallable)
    void MoveToNextPoint();

protected:
    virtual void BeginPlay() override;
};