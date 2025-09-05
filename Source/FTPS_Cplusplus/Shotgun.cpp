// Fill out your copyright notice in the Description page of Project Settings.


#include "Shotgun.h"
#include "Projectile.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "FTPSCharacter.h"

AShotgun::AShotgun()
{
	ProjectileSocketName = "SG_Projectile";
}

void AShotgun::StartAction()
{
	Super::StartAction();
	if (IsValid(CurrentOwnerCharacter))
	{
		USkeletalMeshComponent* CharacterMeshComp = CurrentOwnerCharacter->GetMesh();
		if (CharacterMeshComp)
		{
			FVector ProjectilSocketLocation = CharacterMeshComp->GetSocketLocation(ProjectileSocketName);
			FRotator ProjectilSocketRotation = CharacterMeshComp->GetSocketRotation(ProjectileSocketName);
			AProjectile* CurrentProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectilSocketLocation, ProjectilSocketRotation);
		}
	}
}

void AShotgun::StopAction()
{
	Super::StopAction();
}
