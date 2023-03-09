// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fruit.generated.h"

class USoundCue;

UENUM(BlueprintType)
enum class EFruitType :uint8 {
	Regular,
	PowerUp
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFruitEatenEvent, EFruitType, FruitType);


UCLASS()
class PACMAN_API AFruit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFruit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Consume();

	UPROPERTY(EditAnywhere)
		EFruitType FruitType = EFruitType::Regular;

	UPROPERTY(BlueprintAssignable, BlueprintCallable);
		FFruitEatenEvent FruitEatenEvent;

private:
	UPROPERTY(EditAnywhere)
		USoundCue* ConsumptionSound;
};
