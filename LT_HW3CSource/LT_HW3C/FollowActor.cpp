// Fill out your copyright notice in the Description page of Project Settings.

#include "FollowActor.h"
#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AffectableActor.h"

// Sets default values
AFollowActor::AFollowActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComp->SetSphereRadius(32.0f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFollowActor::SphereBeginOverlap);
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComp->SetupAttachment(RootComponent);

	ChargePower = 20.f;
	LeftOffest = 100.f;
	UpOffest = 80.f;
	ForwardOffest = 100.f;
}

// Called when the game starts or when spawned
void AFollowActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFollowActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isFollowing)
	{
		if (Pawn)
		{
			FVector TLoc;
			FRotator TRot;
			//获取目标位置
			TLoc = Pawn->GetActorLocation() + -LeftOffest * Pawn->GetActorRightVector() + UpOffest * Pawn->GetActorUpVector() + ForwardOffest * Pawn->GetActorForwardVector();
			TRot = Pawn->GetFollowCamera()->GetComponentRotation();
			FVector DLoc;
			FRotator DRot;
			float dlen;
			FVector Direction;
			//计算移动量
			(TLoc - GetActorLocation()).ToDirectionAndLength(Direction, dlen);

			//如果没有到达位置，就靠近到离目标点20cm以内的位置
			//如果到达了位置，直到偏离80cm，都在原地上下漂浮
			if (!IsArrive)
			{
				if (dlen > 20.f)
				{
					DLoc = 200.f * Direction;
					DLoc += Direction * ((dlen - 200.f) > 0 ? dlen : (dlen - 200.f) * 0.0618f);
					DLoc *= DeltaTime;
					AddActorWorldOffset(DLoc);
				}
				else
				{
					IsArrive = 1;
				}
			}
			else
			{
				if (dlen > 80.f)
				{
					IsArrive = 0;
				}
				//漂浮效果
				float RunningTime = GetGameTimeSinceCreation();
				float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
				AddActorWorldOffset(FVector(0, 0, DeltaHeight * 20.f));
				//计算朝向
				DRot = (UKismetMathLibrary::RInterpTo(GetActorRotation(), TRot, DeltaTime, 3.0f));
				SetActorRotation(DRot);
			}
				
			
		}
	}
	else
	{
		AddActorLocalRotation(FRotator(0, 90.f, 0) * DeltaTime);
		
	}

	

	//第三种颜色会一直变
	if (Color == 2)
	{
		float RunningTime = GetGameTimeSinceCreation();
		LightComp->SetLightColor(FColor(FMath::Sin(RunningTime) * 255.f, FMath::Cos(RunningTime) * 255.f, FMath::Sin(-RunningTime) * 255.f, 255), true);
	}
	
}

void AFollowActor::SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//玩家碰到了检测球，开始跟随玩家
	Pawn = Cast<AMyCharacter>(OtherActor);
	if (Pawn)
	{
		if (!isFollowing)
		{
			isFollowing = 1;
			APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
			if (PC)
			{
				EnableInput(PC);
				if (!FirstBindInput)
				{
					FirstBindInput = 1;
					PC->InputComponent->BindAction("Interact", IE_Pressed, this, &AFollowActor::Drop).bConsumeInput = false;
					PC->InputComponent->BindAction("ChangeColor", IE_Pressed, this, &AFollowActor::ChangeColor).bConsumeInput = false;
				}
				
			}
			

		}
	}
}

void AFollowActor::Drop()
{
	if (isFollowing)
	{
		//玩家放下书
		if (Pawn)
		{
			APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
			if (PC)
			{
				DisableInput(PC);
			}
			isFollowing = 0;
		}
	}

}

void AFollowActor::ChangeColor()
{
	if (isFollowing)
	{
		Color = (Color + 1) % LightColors.Num();
		UpdateLightColor();
	}
	
}

void AFollowActor::UpdateLightColor()
{
	if (LightColors.IsValidIndex(Color))
	{
		if (LightComp)
		{
			LightComp->SetLightColor(LightColors[Color], true);
		}
		
	}
}
