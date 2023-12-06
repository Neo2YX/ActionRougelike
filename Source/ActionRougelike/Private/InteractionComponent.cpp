// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "GameplayInterface.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionComponent::PrimaryInteract()
{
	//Line Tracing version
	/*FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + EyeRotation.Vector() * 300;

	FHitResult Hit;
	bool bHitActor = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	AActor* HitActor = Hit.GetActor();
	if (HitActor)
	{
		if (HitActor->Implements<UGameplayInterface>())
		{
			APawn* MyPawn = Cast<APawn>(MyOwner);

			IGameplayInterface::Execute_Interact(HitActor, MyPawn);
		}
	}

	FColor LineColor = bHitActor ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);*/

	//Sphere Tracing Version
	AActor* MyOwner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + EyeRotation.Vector() * TracingDistance;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FCollisionShape SweepShape;
	SweepShape.SetSphere(TracingSphereRadius);

	TArray<FHitResult> Hits;

	bool bHitActor = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, SweepShape);
	FColor LineColor = bHitActor ? HitLineColor : UnhitLineColor;
	for (FHitResult& Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				IGameplayInterface::Execute_Interact(HitActor, MyPawn);
				if (bDrawDebugLine) DrawDebugSphere(GetWorld(), Hit.ImpactPoint, TracingSphereRadius, 0, LineColor, false, DebugLineTime, 0, DebugLineWidth);
				break;
			}
		}
		
		
	}

	if(bDrawDebugLine) DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, DebugLineTime, 0, DebugLineWidth);
}
