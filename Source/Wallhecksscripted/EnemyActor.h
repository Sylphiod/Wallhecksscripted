// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class WALLHECKSSCRIPTED_API AEnemyActor : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* MySphereComponent;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RestTimeBetweenMovements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	TArray<FVector> MovementPoints;

private:
	int32 CurrentPointIndex;
	float CurrentRestTime;
	FVector InitialLocation;

	
};
