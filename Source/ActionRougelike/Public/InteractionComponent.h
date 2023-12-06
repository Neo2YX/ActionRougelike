// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROUGELIKE_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void PrimaryInteract();

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	UPROPERTY(EditAnywhere, category="Interact Tracing", meta=(ClampMin = 0.0f))
	float TracingDistance = 300;
	UPROPERTY(EditAnywhere, category="Interact Tracing", meta=(ClampMin = 0.0f))
	float TracingSphereRadius = 30;
	UPROPERTY(EditAnywhere, category = "Interact Tracing")
	bool bDrawDebugLine = false;
	UPROPERTY(EditAnywhere, category = "Interact Tracing", meta=(EditCondition = "bDrawDebugLine", ClampMin = 0.0f))
	float DebugLineWidth = 2.0f;
	UPROPERTY(EditAnywhere, category = "Interact Tracing", meta=(EditCondition = "bDrawDebugLine"))
	FColor HitLineColor = FColor::Green;
	UPROPERTY(EditAnywhere, category = "Interact Tracing", meta=(EditCondition = "bDrawDebugLine"))
	FColor UnhitLineColor = FColor::Red;
	UPROPERTY(EditAnywhere, category = "Interact Tracing", meta=(EditCondition = "bDrawDebugLine"))
	float DebugLineTime = 2.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
