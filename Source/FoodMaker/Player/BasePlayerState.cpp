#include "BasePlayerState.h"

#include "FoodMaker/Assets/Item/ItemActor.h"

ABasePlayerState::ABasePlayerState()
{
	InventoryList.SetNum(InventoryCount);
}

void ABasePlayerState::AddInventory(AItemActor* NewItem)
{
	for (uint8 i = 0; i < InventoryCount; i++)
	{
		if (AItemActor* CurrentItem = InventoryList[i])
		{
			if (CurrentItem->GetId() == NewItem->GetId())
			{
				if (CurrentItem->GetMaxStack() > CurrentItem->GetStack())
				{
					CurrentItem->SetItemStack(CurrentItem->GetStack() + 1);
					NewItem->Destroy();
					break;
				}
			}
		} else
		{
			InventoryList.Insert(NewItem, i);
			NewItem->Destroy();
			break;
		}
	}
}
