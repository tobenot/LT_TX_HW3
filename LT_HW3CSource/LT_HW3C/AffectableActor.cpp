// Fill out your copyright notice in the Description page of Project Settings.


#include "AffectableActor.h"
#include "Materials/MaterialInstanceConstant.h"

// Sets default values
AAffectableActor::AAffectableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = MeshComp;

	ChargeMax = 100.f;
	LostChargePerSec = 25.f;
	DurationStartLostSinceCharge = 1.5f;


}

// Called when the game starts or when spawned
void AAffectableActor::BeginPlay()
{
	Super::BeginPlay();

	//可以充能的材质
	if (MeshComp)
	{
		
		//UMaterialInstanceConstant* BaseMaterial = Cast<UMaterialInstanceConstant>(MeshComp->GetMaterial(0));
		UMaterialInstanceConstant* BaseMaterial;
		if(ColorMaterials.IsValidIndex(MyColor))
		{
			BaseMaterial = ColorMaterials[MyColor];
			
		}
		else
		{
			BaseMaterial = Cast<UMaterialInstanceConstant>(MeshComp->GetMaterial(0));
		}
		
		if (BaseMaterial)
		{
			ChargeMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, GetWorld());
			MeshComp->SetMaterial(0, ChargeMaterial);
		}
	}
	

}

// Called every frame
void AAffectableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//一段时间没有充能，慢慢损失
	ChargeShield = FMath::Clamp(ChargeShield - DeltaTime, 0.f, DurationStartLostSinceCharge);
	if (ChargeShield < 0.1f)
	{
		if (LostChargePerSec != 0)
		{
			Charge(-LostChargePerSec * DeltaTime, MyColor);
		}
		else
		{
			//LostChargePerSec=0 瞬间损失充能
			Charge(-ChargeAmount, MyColor);
		}
		
	}
}

void AAffectableActor::Charge(float Num,int Color)
{
	//同色才能充能，除非自己的颜色是-1
	if ((MyColor != -1) && (Color != MyColor))
	{
		return;
	}
	if (Num > 0)
	{
		//如果充能，一段时间内不会自然损失充能
		ChargeShield = DurationStartLostSinceCharge;
	}

	//充能
	ChargeAmount = FMath::Clamp(ChargeAmount+Num, 0.f, ChargeMax);

	//！！更改充能材质的参数 
	if (ChargeMaterial)
	{
		ChargeMaterial->SetScalarParameterValue("Emissive Intensity", (ChargeAmount/ChargeMax) * 50.f + 0.25f);
	}
}

bool AAffectableActor::GetChargeReady()
{
	return (ChargeMax - ChargeAmount) < ChargeMax*0.5f;
}

