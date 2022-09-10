// Fill out your copyright notice in the Description page of Project Settings.


#include "Firepit.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AFirepit::AFirepit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComp->SetSphereRadius(64.0f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFirepit::SphereBeginOverlap);
	RootComponent = SphereComp;

	RocksMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rocks"));
	RocksMeshComp->SetupAttachment(RootComponent);

	WoodMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wood"));
	WoodMeshComp->SetupAttachment(RootComponent);
	WoodMeshComp->SetRelativeLocation(FVector(0, 0, -0.7));
	WoodMeshComp->SetRelativeRotation(FRotator(0, 58.7f, 0));
	WoodMeshComp->SetRelativeScale3D(FVector(0.97f));

	AshMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ash"));
	AshMeshComp->SetupAttachment(RootComponent);
	AshMeshComp->SetRelativeLocation(FVector(0, 0, -0.7));
	AshMeshComp->SetRelativeRotation(FRotator(0, 58.7f, 0));
	AshMeshComp->SetRelativeScale3D(FVector(0.416f));

	FirePartComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire"));
	FirePartComp->SetupAttachment(RootComponent);
	FirePartComp->SetRelativeLocation(FVector(0, 0, 13.f));
	FirePartComp->SetRelativeRotation(FRotator(0, 58.7f, 0));
	FirePartComp->SetRelativeScale3D(FVector(1.7f));

	SmokePartComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke"));
	SmokePartComp->SetupAttachment(RootComponent);
	SmokePartComp->SetRelativeLocation(FVector(0, 0, 93.f));
	SmokePartComp->SetRelativeRotation(FRotator(0, 58.7f, 0));
	SmokePartComp->SetRelativeScale3D(FVector(5.f));

	ShadowedLightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("ShadowedLight"));
	ShadowedLightComp->SetupAttachment(RootComponent);
	ShadowedLightComp->SetRelativeLocation(FVector(0, 0, 120.f));
	ShadowedLightComp->SetIntensityUnits(ELightUnits::Lumens);
	ShadowedLightComp->SetIntensity(350.0f);
	ShadowedLightComp->LightColor = FColor(255, 219, 115);
	ShadowedLightComp->AttenuationRadius = 600.f;
	ShadowedLightComp->SourceRadius = 75.f;

	AmbientLightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("AmbientLight"));
	AmbientLightComp->SetupAttachment(RootComponent);
	AmbientLightComp->SetRelativeLocation(FVector(0, 0, 83.f));
	AmbientLightComp->SetIntensityUnits(ELightUnits::Lumens);
	AmbientLightComp->SetIntensity(200.0f);
	AmbientLightComp->LightColor = FColor(255, 219, 115);
	AmbientLightComp->AttenuationRadius = 500.f;
	AmbientLightComp->SourceRadius = 75.f;
	AmbientLightComp->CastShadows = 0;
}

// Called when the game starts or when spawned
void AFirepit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirepit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFirepit::SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (FirePartComp)
	{
		FirePartComp->Deactivate();
	}
	if (ShadowedLightComp)
	{
		ShadowedLightComp->SetVisibility(false);
		ShadowedLightComp->Deactivate();
	}
	if (AmbientLightComp)
	{
		AmbientLightComp->SetVisibility(false);
		AmbientLightComp->Deactivate();
	}
}
		
