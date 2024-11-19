#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

USTRUCT()
struct FItemMeta
{
	GENERATED_BODY()

	// TODO: Enum화 필요
	UPROPERTY(EditDefaultsOnly)
	uint16 Id;
	
	UPROPERTY(EditDefaultsOnly)
	FString DisplayName;

	UPROPERTY(EditDefaultsOnly)
	TArray<FString> Description;

	UPROPERTY(EditDefaultsOnly)
	uint16 MaxStack = 10;

	UPROPERTY(EditDefaultsOnly)
	uint16 Stack = 1;

	UPROPERTY(EditDefaultsOnly)
	TMap<FString, FString> Meta;
};

UCLASS()
class FOODMAKER_API AItemActor : public AActor
{
	GENERATED_BODY()

public:
	AItemActor();

	FORCEINLINE uint16 GetId() const { return ItemMeta.Id; }
	FORCEINLINE FString GetDisplayName() const { return ItemMeta.DisplayName; }
	FORCEINLINE uint16 GetStack() const { return ItemMeta.Stack; }
	FORCEINLINE uint16 GetMaxStack() const { return ItemMeta.MaxStack; }
	FORCEINLINE TArray<FString> GetDescription() const { return ItemMeta.Description; }
	FORCEINLINE TMap<FString, FString> GetMeta() const { return ItemMeta.Meta; }
	FORCEINLINE TObjectPtr<UTexture2D> GetTexture() const { return Thumbnail; }
	FORCEINLINE void SetItemStack(const uint8 NewStack) { ItemMeta.Stack = NewStack; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> Thumbnail;
	
	UPROPERTY(EditDefaultsOnly)
	uint16 ItemId = 0;
	
	FItemMeta ItemMeta = {};
};
