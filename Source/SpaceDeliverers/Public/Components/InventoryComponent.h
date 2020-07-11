#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingData.h"
#include "InventoryComponent.generated.h"

class UUserWidget;
class UInventoryWidget;
enum GemType;
struct FBuildingData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEDELIVERERS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	void CollectCrystal(GemType type);

	FORCEINLINE const TArray<int>& GetGems() { return Gems; }
	void SpendGems(FBuildingData& data);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> InventoryWidgetBP;

	UPROPERTY()
	UInventoryWidget* InventoryWidget;

private:
	void UpdateUI();

	UPROPERTY()
	TArray<int> Gems;
		
};
