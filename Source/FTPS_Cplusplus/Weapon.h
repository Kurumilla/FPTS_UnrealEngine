// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UDamageType;
class AFTPSCharacter;

UCLASS()
class FTPS_CPLUSPLUS_API AWeapon : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	AFTPSCharacter* CurrentOwnerCharacter;
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void BP_StartAction();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void BP_StopAction();

	UFUNCTION(BlueprintCallable)
	void SetCharacterOwner(AFTPSCharacter* NewOwner);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void StartAction();

	UFUNCTION(BlueprintCallable)
	virtual void StopAction();

};
