// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BotSpawner.generated.h"

class UBillboardComponent;
class ABot;

UCLASS()
class FTPS_CPLUSPLUS_API ABotSpawner : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBillboardComponent* SpawnerBillboardComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	bool bIsActive;

	UPROPERTY(BlueprintReadOnly, Category = "Spawner")
	int CurrentBotsCounter;
	
public:	
	// Sets default values for this actor's properties
	ABotSpawner();
	 
	void NotifyBotDead();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
