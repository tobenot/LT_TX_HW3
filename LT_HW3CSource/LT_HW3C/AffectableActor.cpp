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

	//���Գ��ܵĲ���
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

	//һ��ʱ��û�г��ܣ�������ʧ
	ChargeShield = FMath::Clamp(ChargeShield - DeltaTime, 0.f, DurationStartLostSinceCharge);
	if (ChargeShield < 0.1f)
	{
		if (LostChargePerSec != 0)
		{
			Charge(-LostChargePerSec * DeltaTime, MyColor);
		}
		else
		{
			//LostChargePerSec=0 ˲����ʧ����
			Charge(-ChargeAmount, MyColor);
		}
		
	}
}

void AAffectableActor::Charge(float Num,int Color)
{
	//ͬɫ���ܳ��ܣ������Լ�����ɫ��-1
	if ((MyColor != -1) && (Color != MyColor))
	{
		return;
	}
	if (Num > 0)
	{
		//������ܣ�һ��ʱ���ڲ�����Ȼ��ʧ����
		ChargeShield = DurationStartLostSinceCharge;
	}

	//����
	ChargeAmount = FMath::Clamp(ChargeAmount+Num, 0.f, ChargeMax);

	//�������ĳ��ܲ��ʵĲ��� 
	if (ChargeMaterial)
	{
		ChargeMaterial->SetScalarParameterValue("Emissive Intensity", (ChargeAmount/ChargeMax) * 50.f + 0.25f);
	}
}

bool AAffectableActor::GetChargeReady()
{
	return (ChargeMax - ChargeAmount) < ChargeMax*0.5f;
}

