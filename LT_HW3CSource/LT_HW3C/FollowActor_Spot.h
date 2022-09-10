// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FollowActor.h"
#include "FollowActor_Spot.generated.h"

/**
 * 
 */
UCLASS()
class LT_HW3C_API AFollowActor_Spot : public AFollowActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpotLightComponent* SpotLight;
public:
	AFollowActor_Spot();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightParameter)
		float LightDistance;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
