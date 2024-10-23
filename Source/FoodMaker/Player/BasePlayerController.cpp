#include "BasePlayerController.h"
#include "FoodMaker/Assets/Machine/DefaultMachine.h"
#include "FoodMaker/Widgets/InteractionHUD.h"
#include "Blueprint/UserWidget.h"

void ABasePlayerController::BeginPlay()
{
	if (!InteractionHUD)
	{
		InteractionHUD = CreateWidget<UInteractionHUD>(this, InteractionHUDClass);
	}
}

void ABasePlayerController::SetSelectedInteractiveMachine(const TObjectPtr<ADefaultMachine> Machine)
{
	if (InteractionHUD)
	{
		if (!IsValid(Machine))
        {
			if (!InteractionHUD->IsVisible()) return;
			InteractionHUD->RemoveFromParent();
			SelectedInteractiveMachine = nullptr;
        	return;
        }
		
		if (!InteractionHUD->IsVisible())
		{
			InteractionHUD->AddToViewport();	
		}
		
		if (SelectedInteractiveMachine != Machine)
        {
            InteractionHUD->SetInteractionText(Machine->GetDisplayText());
        }
	}
	
	SelectedInteractiveMachine = Machine;
}
