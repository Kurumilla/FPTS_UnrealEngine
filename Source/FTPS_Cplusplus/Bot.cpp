// Fill out your copyright notice in the Description page of Project Settings.


#include "Bot.h"
#include "Components/StaticMeshComponent.h"
#include "FTPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "DrawDebugHelpers.h"
#include "HealthComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/SphereComponent.h"
#include "BotSpawner.h"

// Sets default values
ABot::ABot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BotMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BotMeshComponent"));
	BotMeshComponent->SetCanEverAffectNavigation(false);
	BotMeshComponent->SetSimulatePhysics(true);
	RootComponent = BotMeshComponent;

	MinDistanceToTarget = 100.0f;
	ForceMagnitude = 500.0f;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	SelfDestructionDetectorComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SelfDestructionDetector"));
	SelfDestructionDetectorComponent->SetupAttachment(RootComponent);
	SelfDestructionDetectorComponent->SetCollisionResponseToAllChannels(ECR_Ignore); 
	SelfDestructionDetectorComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SelfDestructionDetectorComponent->SetSphereRadius(ExplosionDetector);

	ExplosionDamage = 100.0f;
	ExplosionRadius = 100.0f;
	ExplosionDetector = 250.0f;
}

FVector ABot::GetNextPathPoint()
{
	if (!IsValid(PlayerCharacter))
	{
		return GetActorLocation();
	}
	UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToActorSynchronously(GetWorld(), GetActorLocation(), PlayerCharacter);
	if (NavigationPath->PathPoints.Num() > 1)
	{
		return NavigationPath->PathPoints[1];
	}
	return FVector();
}

void ABot::SelfDamage()
{
	UGameplayStatics::ApplyDamage(this, 20.0f, GetInstigatorController(), nullptr, nullptr);
}

void ABot::SelfDestruction()
{
	if (bIsExplored)
	{
		return;
	}

	bIsExplored = true;

	TArray<AActor*> IgnorActors;
	IgnorActors.Add(this);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), ExplosionDamage, GetActorLocation(), 
		ExplosionRadius, nullptr, IgnorActors, this, GetInstigatorController(), true);

	if (bDebug)
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosionRadius, 20, FColor::Red, true, 5.0f, 0.0f, 2.0f);
	}

	if (IsValid(MySpawner))
	{
		MySpawner->NotifyBotDead();
	}

	Destroy();
}

void ABot::StartCountDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsStartingCountdown)
	{
		return;
	}
	if (OtherActor == PlayerCharacter)
	{
		bIsStartingCountdown = true;
		GetWorld()->GetTimerManager().SetTimer(TimerHandleDamage, this, &ABot::SelfDamage, 0.5f, true);
	}
}

void ABot::TakingDamage(UHealthComponent* CurrentHealthComponent,
	AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsValid(BotMaterial))
	{
		BotMaterial->SetScalarParameterValue("Pulse", GetWorld()->TimeSeconds);
	}

	if (CurrentHealthComponent->IsDead())
	{
		SelfDestruction();
	}
}

// Called when the game starts or when spawned
void ABot::BeginPlay()
{
	Super::BeginPlay();
	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		PlayerCharacter = Cast<AFTPSCharacter>(PlayerPawn);
	}

	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &ABot::TakingDamage);

	SelfDestructionDetectorComponent->OnComponentBeginOverlap.AddDynamic(this, &ABot::StartCountDown);

	BotMaterial = BotMeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, BotMeshComponent->GetMaterial(0));

	NextPathPoint = GetNextPathPoint();
}

// Called every frame
void ABot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float DistanceToTarget = (GetActorLocation() - NextPathPoint).Size();

	if (DistanceToTarget <= MinDistanceToTarget)
	{
		NextPathPoint = GetNextPathPoint();
	}
	else
	{
		FVector ForceDirection = NextPathPoint - GetActorLocation();
		ForceDirection.Normalize();
		ForceDirection *= ForceMagnitude;

		BotMeshComponent->AddForce(ForceDirection, NAME_None, true);
	}

	if (bDebug)
	{
		DrawDebugSphere(GetWorld(), NextPathPoint, 30.0f, 15, FColor::Purple, false, 0.0f, 0, 1.0f);
	}
}

// Called to bind functionality to input
void ABot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

