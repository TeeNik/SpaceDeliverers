#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UUserWidget;
class UInventoryWidget;
enum GemType;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEDELIVERERS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	void CollectCrystal(GemType type);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> InventoryWidgetBP;

	UPROPERTY()
	UInventoryWidget* InventoryWidget;

private:
	UPROPERTY()
	TArray<int> Gems;
		
};
