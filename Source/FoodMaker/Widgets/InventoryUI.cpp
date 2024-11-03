#include "InventoryUI.h"

#include "Components/GridPanel.h"
#include "Components/UniformGridPanel.h"
#include "FoodMaker/Assets/Item/ItemableActor.h"
#include "FoodMaker/Player/BasePlayerState.h"
#include "FoodMaker/Widgets/InventoryItemWidget.h"

void UInventoryUI::NativeConstruct()
{
	if (ABasePlayerState* PlayerState = Cast<ABasePlayerState>(GetOwningPlayerState()))
	{
		for (FInventoryData InventoryData : PlayerState->GetInventoryDataList())
		{
			if (AItemableActor* Item = InventoryData.ItemInfo.GetDefaultObject())
			{
				InventorySequenceMap.Add(Item->GetId(), InventoryData.Count);
				InventoryItemListMap.Add(Item->GetId(), Item);

				UInventoryItemWidget* InventoryItem =
					CreateWidget<UInventoryItemWidget>(this, InventoryItemWidgetClass);

				// TODO: InventoryItem의 GridSlot에 대해 값을 설정하면 완료
				
				InventoryGrid->AddChild(Cast<UWidget>(InventoryItem));

			}
		}
	}
}

void UInventoryUI::NativeDestruct()
{
	if (ABasePlayerState* PlayerState = Cast<ABasePlayerState>(GetOwningPlayerState()))
	{
		TArray<FInventoryData> NewItemList;	
		for (FInventoryData InventoryDataList : PlayerState->GetInventoryDataList())
		{
			if (AItemableActor* Item = Cast<AItemableActor>(InventoryDataList.ItemInfo.Get()))
			{
				NewItemList.Add({Item->GetClass(), InventorySequenceMap[Item->GetId()]});
				InventorySequenceMap.Add(Item->GetId(), InventoryDataList.Count);
			}
		}

		PlayerState->SetInventoryDataList(NewItemList);
	}
}

