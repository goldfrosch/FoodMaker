#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemWidget.generated.h"

class UImage;
class UTextBlock;
class AItemActor;

UCLASS()
class FOODMAKER_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetItemCount(const uint8 Count);
	void SetThumbnail(UTexture2D* Texture);
	
	TObjectPtr<AItemActor> ItemActor;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CountTextBlock;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Thumbnail;

};
