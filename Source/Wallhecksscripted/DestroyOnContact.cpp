// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyOnContact.h"
#include "DestroyOnContact.h"
#include "Components/SphereComponent.h"

// Sets default values
ADestroyOnContact::ADestroyOnContact()
{
	MySphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MySphereComponent->InitSphereRadius(100.f);
	MySphereComponent->SetCollisionProfileName(TEXT("Trigger"));
	RootComponent = MySphereComponent;

	MySphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADestroyOnContact::OnOverlapBegin);
}

void ADestroyOnContact::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();
}