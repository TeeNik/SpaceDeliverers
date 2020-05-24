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
	
	void Build(const AActor* dest, const float duration);

	UFUNCTION(BlueprintImplementableEvent, Category = "BuildingBot")
	void OnBuildBP(const AActor* dest, const float duration);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnReturnToHome();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	const AActor* Home = nullptr;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> BuilderWidgetBP;

	UPROPERTY()
	UBuilderWidget* BuilderWidget;

	FBuildingSelected OnBuildingSelected;
	UInteractionComponent* InteractionComponent;

	UFUNCTION()
	void BuildingSelected();

	bool IsBusy = false;
};
