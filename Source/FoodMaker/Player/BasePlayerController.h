#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class ADefaultMachine;
class UInteractionHUD;

UCLASS()
class FOODMAKER_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void SetSelectedInteractiveMachine(const TObjectPtr<ADefaultMachine> Machine);

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UInteractionHUD> InteractionHUDClass;

	UPROPERTY()
	TObjectPtr<UInteractionHUD> InteractionHUD;

	UPROPERTY()
	TObjectPtr<ADefaultMachine> SelectedInteractiveMachine;
};
