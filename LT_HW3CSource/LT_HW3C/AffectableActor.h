// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AffectableActor.generated.h"

UCLASS()
class LT_HW3C_API AAffectableActor : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* MeshComp;

public:	
	// Sets default values for this actor's properties
	AAffectableActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightParameter)
		int MyColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightParameter)
		TArray<class UMaterialInstanceConstant*> ColorMaterials;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AffectableActor)
		float ChargeAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AffectableActor)
		float ChargeMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AffectableActor)
		float LostChargePerSec;
	//接受充能的多少秒后重新失去充能
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AffectableActor)
		float DurationStartLostSinceCharge;
		float ChargeShield;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AffectableActor)
		UMaterialInstanceDynamic* ChargeMaterial;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void Charge(float Num,int Color);
	UFUNCTION()
		bool GetChargeReady();
};
