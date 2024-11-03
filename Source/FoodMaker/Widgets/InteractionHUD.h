#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "InteractionHUD.generated.h"

class UTextBlock;

UCLASS()
class FOODMAKER_API UInteractionHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> InteractionText;

	FORCEINLINE void SetInteractionText(const FString NewText)
	{
		InteractionText->SetText(FText::FromString(NewText));
	}
};
