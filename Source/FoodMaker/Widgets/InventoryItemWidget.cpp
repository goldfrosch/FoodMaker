#include "InventoryItemWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

	
void UInventoryItemWidget::SetItemCount(const uint8 Count)
{
	CountTextBlock->SetText(FText::FromString(*FString::FromInt(Count)));
}

void UInventoryItemWidget::SetThumbnail(UTexture2D* Texture)
{
	Thumbnail->SetBrushFromTexture(Texture, false);
}
