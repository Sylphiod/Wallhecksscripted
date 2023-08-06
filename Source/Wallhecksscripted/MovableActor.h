// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveableActor.generated.h"

UCLASS()
class WALLHECKSSCRIPTED_API AMovableActor : public AActor
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
                            
                                UFUNCTION()
                                void TimelineCallback(float Value);
                            
                                UFUNCTION()
                                void TimelineFinishedCallback();
                            
                                UFUNCTION(BlueprintCallable)
                                void MoveToNextPoint();
                            };