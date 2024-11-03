#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FoodMaker/Data/InventoryData.h"
#include "BasePlayerState.generated.h"

UCLASS()
class FOODMAKER_API ABasePlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ABasePlayerState();

	FORCEINLINE TArray<FInventoryData> GetInventoryDataList()
	{
		return InventoryDataList;
	}

	FORCEINLINE void SetInventoryDataList(TArray<FInventoryData> NewList)
	{
		// 메모리 비어주는 작업 미리 수행해주기
		InventoryDataList.Reset();
		// 새로운 메모리 주소로 할당하기
		InventoryDataList = NewList;
	}
	
	TArray<FInventoryData> InventoryDataList;
};
