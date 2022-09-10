// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowActor_Point.h"
#include "MyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AffectableActor.h"

AFollowActor_Point::AFollowActor_Point()
{
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);
	LightComp = PointLight;
	LightRadius = 512.f;

	LeftOffest = -LeftOffest;
}

void AFollowActor_Point::BeginPlay()
{
	Super::BeginPlay();
	UpdateLightColor();
}

void AFollowActor_Point::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//影响能被光充能的物件
	const FVector Start = GetActorLocation();
	const FVector End = GetActorLocation();
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
