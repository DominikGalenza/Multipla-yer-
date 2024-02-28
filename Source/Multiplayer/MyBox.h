// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "MyBox.generated.h"

UCLASS()
class MULTIPLAYER_API AMyBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(ReplicatedUsing = OnRep_ReplicatedVariable, BlueprintReadWrite)
	float ReplicatedVariable;
	UPROPERTY(EditAnywhere)
	UParticleSystem* ExplosionEffect;

	FTimerHandle TestTimer;

	UFUNCTION(BlueprintCallable)
	void OnRep_ReplicatedVariable();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCExplode();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void DecreaseReplicatedVariable();
};
