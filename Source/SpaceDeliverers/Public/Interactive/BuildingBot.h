#pragma once

#include "CoreMinimal.h"
#include "Interactive.h"
#include "GameFramework/Character.h"
#include "BuildingBot.generated.h"

class UBuilderWidget;
class UUserWidget;
class UInteractionComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBuildingSelected);

UCLASS()
class SPACEDELIVERERS_API ABuildingBot : public ACharacter, public IInteractive
{
	GENERATED_BODY()

public:
	ABuildingBot();

	virtual bool Interact(class UInteractionComponent* interComp, ACharacter* character) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ABuilder> BuilderBase;

	virtual void OnSelect(class UInteractionComponent* interComp) override;
	virtual void OnDeselect() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> BuilderWidgetBP;

	UPROPERTY()
	UBuilderWidget* BuilderWidget;

	FBuildingSelected OnBuildingSelected;
	UInteractionComponent* InteractionComponent;

	UFUNCTION()
	void BuildingSelected();

};
