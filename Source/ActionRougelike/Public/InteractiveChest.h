// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayInterface.h"
#include "InteractiveChest.generated.h"

UCLASS()
class ACTIONROUGELIKE_API AInteractiveChest : public AActor, public IGameplayInterface
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AInteractiveChest();

	UPROPERTY(EditAnywhere, category = "Chest", meta = (ClampMax = 180.0f, ClampMin = 0.0f));
	float TargetPitch = 120.0f;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMeshComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMeshComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void Interact_Implementation(APawn* InstigatorPawn) override;

};
