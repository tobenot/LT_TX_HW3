// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FollowActor.h"
#include "Components/PointLightComponent.h"
#include "FollowActor_Point.generated.h"

/**
 * 
 */
UCLASS()
class LT_HW3C_API AFollowActor_Point : public AFollowActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UPointLightComponent* PointLight;
public:
	AFollowActor_Point();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
