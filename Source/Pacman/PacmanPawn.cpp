// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanPawn.h"
#include "Fruit.h"

// Sets default values
APacmanPawn::APacmanPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	frozen = true;
	invincible = false;
	maxInvincibleTime = 5.0f;
}

// Called when the game starts or when spawned
void APacmanPawn::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &APacmanPawn::OnOverlapBegin);
}

// Called every frame
void APacmanPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!frozen) {
		AddMovementInput(GetActorForwardVector());
	}
}

// Called to bind functionality to input
void APacmanPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APacmanPawn::SetDirection(const FVector Direction)
{
	if (Direction == FVector::UpVector) {
		SetActorRotation(FRotator(0, -90, 0));
	}
	else if (Direction == FVector::DownVector) {
		SetActorRotation(FRotator(0, 90, 0));
	}
	else if (Direction == FVector::RightVector) {
		SetActorRotation(FRotator(0, 0, 0));
	}
	else if (Direction == FVector::LeftVector) {
		SetActorRotation(FRotator(0, 180, 0));
	}
}

void APacmanPawn::ResetInvincible()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("I am no longer invincible"));
	invincible = false;
}

void APacmanPawn::OnOverlapBegin(AActor* PlayerActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Fruit.Regular")) {
		Cast <AFruit>(OtherActor)->Consume();
	}
	if (OtherActor->ActorHasTag("Fruit.Special")) {
		Cast <AFruit>(OtherActor)->Consume();

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("I am invincible"));
		invincible = true;
		
		//start invincible timer
		GetWorld()->GetTimerManager().SetTimer(invincibleTimerHandle, this, &APacmanPawn::ResetInvincible, maxInvincibleTime, false);
	}
	if (OtherActor->ActorHasTag("Ghost")) {
		if (invincible) {
			//eat ghost
		}
		else {
			//implement death
		}
	}
}



