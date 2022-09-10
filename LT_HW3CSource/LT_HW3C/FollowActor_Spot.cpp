// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowActor_Spot.h"
#include "AffectableActor.h"
#include "FollowActor.h"
#include "Components/SpotLightComponent.h"
#include "MyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

AFollowActor_Spot::AFollowActor_Spot()
{
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(RootComponent);
	LightComp = SpotLight;
	LightRadius = 80.f;
	LightDistance = 512.f;
}

void AFollowActor_Spot::BeginPlay()
{
	Super::BeginPlay();
	UpdateLightColor();
}

void AFollowActor_Spot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//影响能被光充能的物件
	const FVector Start = GetActorLocation() + GetActorForwardVector() * LightRadius;
	const FVector End = GetActorLocation() + GetActorForwardVector() * LightDistance;
	const float TraceRadius = LightRadius;
	const bool IgnoreSelf = true;
	//不要检测的actors
	TArray<AActor*> ActorsToIgnore;
	if (Pawn)
	{
		ActorsToIgnore.Add(Pawn);
		ActorsToIgnore.Add(this);
	}
	//检查的结果
	TArray<FHitResult> HitArray;
	//要检测的类型
	const TArray<TEnumAsByte<EObjectTypeQuery>> DesireObjects = {
		UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic),
	};
	//检测的结果
	const bool Hit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, TraceRadius,
		DesireObjects, false, ActorsToIgnore, EDrawDebugTrace::None, HitArray, IgnoreSelf,
		FLinearColor::Red, FLinearColor::Green, 5.0f);

	if (Hit)
	{
		for (const FHitResult HitResult : HitArray)
		{
			//检测之后的循环处理
			auto Stone = Cast<AAffectableActor>(HitResult.Actor);
			if (Stone)
			{
				Stone->Charge(DeltaTime * ChargePower, Color);
			}
		}
	}
}
