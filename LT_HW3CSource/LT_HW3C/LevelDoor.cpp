// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDoor.h"
#include "AffectableActor.h"

// Sets default values
ALevelDoor::ALevelDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!DoorOpen)
	{
		bool flag = 1;
		for (AAffectableActor* Stone : MyStones)
		{
			if (Stone)
			{
				if (!Stone->GetChargeReady())
				{
					flag = 0;
					break;
				}
			}

		}
		if (flag)
		{
			DoorOpen = 1;
			//开门效果
			TArray<UActorComponent*> StaticMeshComps;
			StaticMeshComps = GetComponentsByClass(UStaticMeshComponent::StaticClass());

			for (UActorComponent* TpActorCom : StaticMeshComps)
			{
				UStaticMeshComponent* TpMeshCom = Cast<UStaticMeshComponent>(TpActorCom);
				if (TpMeshCom)
				{
					//TpMeshCom->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
					//TpMeshCom->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
					//TpMeshCom->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
					TpMeshCom->SetSimulatePhysics(true);
				}
			}
		}
	}
	
}

