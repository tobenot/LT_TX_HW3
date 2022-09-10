// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelDoor.generated.h"

UCLASS()
class LT_HW3C_API ALevelDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelDoor();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Door)
		TArray<class AAffectableActor*> MyStones;

	bool DoorOpen;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
