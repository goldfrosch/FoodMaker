#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultMachine.generated.h"

UCLASS()
class FOODMAKER_API ADefaultMachine : public AActor
{
	GENERATED_BODY()

public:
	ADefaultMachine();

	FORCEINLINE FString GetDisplayText() { return DisplayText; }

protected:
	virtual void BeginPlay() override;
	
    virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> AssetMesh;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	FString DisplayText;
};
