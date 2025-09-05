// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/SphereComponent.h"
#include "FTPSCharacter.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	MainColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MainColliderComponent"));
	MainColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MainColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = MainColliderComponent;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem::Pickup(AFTPSCharacter* PickupActor)
{
	BP_Pickup(PickupActor);
}

void AItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsValid(OtherActor))
	{
		AFTPSCharacter* OverlapCharacter = Cast<AFTPSCharacter>(OtherActor);
		if (IsValid(OverlapCharacter) && OverlapCharacter->GetCharacterType() == FTPSCharacterType::CharacterType_Player)
		{
			Pickup(OverlapCharacter);
		}
	}

}

