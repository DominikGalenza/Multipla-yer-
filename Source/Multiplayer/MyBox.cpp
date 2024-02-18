// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBox.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AMyBox::AMyBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ReplicatedVariable = 100.0f;
	//bReplicates = true;
}

// Called when the game starts or when spawned
void AMyBox::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Server"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("Client"));
	}

	SetReplicates(true);
	SetReplicateMovement(true);

	if (HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &AMyBox::DecreaseReplicatedVariable, 2.0f, false);
	}
}

// Called every frame
void AMyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyBox, ReplicatedVariable);
}

void AMyBox::OnRep_ReplicatedVariable()
{
	if (HasAuthority())
	{
		FVector NewLocation = GetActorLocation() + FVector(0.0f, 0.0f, 200.0f);
		SetActorLocation(NewLocation);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Server: OnRep_ReplicatedVariable"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("Client %d: OnRep_ReplicatedVariable"), GPlayInEditorID));
	}
}

void AMyBox::DecreaseReplicatedVariable()
{
	if (HasAuthority())
	{
		ReplicatedVariable -= 1.0f;
		OnRep_ReplicatedVariable();
		if (ReplicatedVariable > 0)
		{
			GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &AMyBox::DecreaseReplicatedVariable, 2.0f, false);
		}
	}
}
