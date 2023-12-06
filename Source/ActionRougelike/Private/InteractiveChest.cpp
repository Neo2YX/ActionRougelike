// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveChest.h"

// Sets default values
AInteractiveChest::AInteractiveChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMeshComp;

	LidMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lid Mesh"));
	LidMeshComp->SetupAttachment(BaseMeshComp);

}

// Called when the game starts or when spawned
void AInteractiveChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractiveChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractiveChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMeshComp->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

