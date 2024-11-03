#pragma once

#include "CoreMinimal.h"
#include "InventoryData.generated.h"

class AItemableActor;

USTRUCT(Blueprintable)
struct FInventoryData
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TSubclassOf<AItemableActor> ItemInfo;

	uint16 Count;
};
