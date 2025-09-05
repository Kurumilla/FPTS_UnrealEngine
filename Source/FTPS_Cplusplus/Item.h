// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;
class AFTPSCharacter;

UCLASS()
class FTPS_CPLUSPLUS_API AItem : public AActor
{

	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USphereComponent* MainColliderComponent;

public:

	AItem();

protected:

	virtual void BeginPlay() override;

	virtual void Pickup(AFTPSCharacter* PickupActor);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
	void BP_Pickup(AFTPSCharacter* PickupActor);

public:

	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
