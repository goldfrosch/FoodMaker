#include "InventoryUI.h"

#include "Components/WrapBox.h"
#include "FoodMaker/Assets/Item/ItemActor.h"
#include "FoodMaker/Player/BasePlayerState.h"
#include "FoodMaker/Widgets/InventoryItemWidget.h"

void UInventoryUI::SetInventoryData(TArray<AItemActor*> InitData)
{
	InventoryData = &InitData;
}

void UInventoryUI::NativeConstruct()
{
	ABasePlayerState* PS = Cast<ABasePlayerState>(GetOwningPlayerState());
	check(PS);
	
	if (!IsInitialized)
	{
		for (uint8 i = 0; i < PS->InventoryCount; i++)
		{
			UInventoryItemWidget* InventoryItem =
						CreateWidget<UInventoryItemWidget>(this, InventoryItemWidgetClass);
			InventorySlotList->AddChild(InventoryItem);
		}
		
		IsInitialized = true;
	}

	for (uint8 i = 0; i < PS->InventoryCount; i++)
	{
		if (UInventoryItemWidget* ItemWidget = Cast<UInventoryItemWidget>(InventorySlotList->GetAllChildren()[i]))
        {
			if (PS->InventoryList[i])
			{
				if (PS->InventoryList[i]->GetTexture()) ItemWidget->SetThumbnail(PS->InventoryList[i]->GetTexture());
        		if (PS->InventoryList[i]->GetStack()) ItemWidget->SetItemCount(PS->InventoryList[i]->GetStack());
			}
        }
	}
}

void UInventoryUI::NativeDestruct()
{
}

