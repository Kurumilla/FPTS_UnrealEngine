// Fill out your copyright notice in the Description page of Project Settings.


#include "ANSMelee.h"
#include "FTPSCharacter.h"

void UANSMelee::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	AActor* CharacterActor = MeshComp->GetOwner();
	if (IsValid(CharacterActor))
	{
		AFTPSCharacter* Character = Cast<AFTPSCharacter>(CharacterActor);
		if (IsValid(Character))
		{
			Character->SetMeleeDetectorCollision(ECollisionEnabled::QueryOnly);
			UE_LOG(LogTemp, Warning, TEXT("Entre NotifyBegin"));
		}
	}
}

void UANSMelee::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();
	if (IsValid(CharacterActor))
	{
		AFTPSCharacter* Character = Cast<AFTPSCharacter>(CharacterActor);
		if (IsValid(Character))
		{
			Character->SetMeleeDetectorCollision(ECollisionEnabled::NoCollision);
			UE_LOG(LogTemp, Warning, TEXT("Entre NotifyEnd"));
		}
	}
}
