#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BasePlayerState.generated.h"

class AItemActor;

UCLASS()
class FOODMAKER_API ABasePlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ABasePlayerState();
	
	UPROPERTY(EditDefaultsOnly, Category="Options", meta = (AllowPrivateAccess = true))
	uint8 InventoryCount = 30;

	UPROPERTY()
	TArray<AItemActor*> InventoryList;

	void AddInventory(AItemActor* NewItem);
};
