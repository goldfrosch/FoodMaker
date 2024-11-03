#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

class UGridPanel;
class UInventoryItemWidget;
class AItemableActor;

UCLASS()
class FOODMAKER_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGridPanel> InventoryGrid;
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	TMap<FString, uint16> InventorySequenceMap;
	TMap<FString, AItemableActor*> InventoryItemListMap;
	
	UPROPERTY(EditDefaultsOnly, Category="Options", meta = (AllowPrivateAccess = true))
	uint8 InventoryWidth;
	
	UPROPERTY(EditDefaultsOnly, Category="Options", meta = (AllowPrivateAccess = true))
	uint8 InventoryHeight;
	
	UPROPERTY(EditDefaultsOnly, Category="Options", meta = (AllowPrivateAccess = true))
	TSubclassOf<UInventoryItemWidget> InventoryItemWidgetClass;
};
