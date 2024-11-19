#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

class AItemActor;
class UWrapBox;
class UInventoryItemWidget;

UCLASS()
class FOODMAKER_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetInventoryData(TArray<AItemActor*> InitData);
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	bool IsInitialized = false;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWrapBox> InventorySlotList;
	
	TArray<AItemActor*>* InventoryData;
	
	UPROPERTY(EditDefaultsOnly, Category="Options", meta = (AllowPrivateAccess = true))
	TSubclassOf<UInventoryItemWidget> InventoryItemWidgetClass;
};
