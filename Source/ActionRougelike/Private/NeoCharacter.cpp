// Fill out your copyright notice in the Description page of Project Settings.


#include "NeoCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ANeoCharacter::ANeoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ANeoCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANeoCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector(), Value);
}

void ANeoCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	FVector RightVec = FVector::CrossProduct(GetActorUpVector(), ControlRot.Vector());
	RightVec.Normalize();
	AddMovementInput(RightVec, Value);
}

void ANeoCharacter::PrimaryAttack()
{
	FVector HandLocation = GetMesh()->GetSocketLocation(TEXT("Muzzle_01"));

	FTransform SpawnTF = FTransform(GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTF, SpawnParams);
}

// Called every frame
void ANeoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANeoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Move Character
	PlayerInputComponent->BindAxis("MoveForward", this, &ANeoCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANeoCharacter::MoveRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ANeoCharacter::Jump);


	//Move Camera
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//Attack
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ANeoCharacter::PrimaryAttack);
}

