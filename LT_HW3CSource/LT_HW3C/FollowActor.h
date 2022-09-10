// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FollowActor.generated.h"


UCLASS()
class LT_HW3C_API AFollowActor : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* SphereComp;
public:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//子类的灯光组件的引用
	class ULightComponent* LightComp;

public:	
	// Sets default values for this actor's properties
	AFollowActor();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightParameter)
		int Color;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightParameter)
		float LightRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightParameter)
		float ChargePower;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FollowActor)
		bool isFollowing;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FollowActor)
		bool IsArrive;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FollowActor)
		class AMyCharacter* Pawn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FollowActor)
		bool FirstBindInput;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = LightParameter)
		TArray<FColor> LightColors;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FollowActor)
		float LeftOffest;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FollowActor)
		float UpOffest; 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FollowActor)
		float ForwardOffest;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void Drop();
	UFUNCTION()
		void ChangeColor();
	UFUNCTION()
		void UpdateLightColor();
};
