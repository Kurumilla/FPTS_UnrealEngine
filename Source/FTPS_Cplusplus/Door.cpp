// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/BoxComponent.h"
#include "FTPSCharacter.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot"));
	RootComponent = CustomRootComponent;

	DoorFrameComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrameComponent->SetupAttachment(CustomRootComponent);

	DoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorComponent->SetupAttachment(CustomRootComponent);

	KeyZoneColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("KeyZoneCollider"));
	KeyZoneColliderComponent->SetupAttachment(CustomRootComponent);
	KeyZoneColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	KeyZoneColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	KeyZoneColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	OpenAngle = -90.0;
	DoorTag = "KeyA";

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	KeyZoneColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &ADoor::CheckKeyFromPlayer);
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::CheckKeyFromPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool BFromSweep, const FHitResult& SweepResult)
{
	if (bIsOpen)
	{
		return;
	}
	if (IsValid(OtherActor))
	{
		AFTPSCharacter* OverlapCharacter = Cast<AFTPSCharacter>(OtherActor);
		if (IsValid(OverlapCharacter))
		{
			if (OverlapCharacter->HasKey(DoorTag) && OverlapCharacter->GetCharacterType() == FTPSCharacterType::CharacterType_Player)
			{
				OpenDoor();
			}
		}
	}
}

void ADoor::OpenDoor()
{
	FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f);
	DoorComponent->SetRelativeRotation(NewRotation);

	bIsOpen = true;
}

