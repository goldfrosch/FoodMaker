// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemableActor.generated.h"

UCLASS()
class FOODMAKER_API AItemableActor : public AActor
{
	GENERATED_BODY()

public:
	AItemableActor();

	FORCEINLINE FString GetId() { return Id; }
	FORCEINLINE FString GetDisplayName() { return DisplayName; }
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	FString Id;
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	FString DisplayName;
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	uint16 MaxCount = 99;
};
