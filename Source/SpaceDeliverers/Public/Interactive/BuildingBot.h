#pragma once

#include "CoreMinimal.h"
#include "Interactive.h"
#include "GameFramework/Character.h"
#include "BuildingBot.generated.h"

class UBuilderWidget;
class UUserWidget;
class UInteractionComponent;
class ABuildingPlatform;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuildingSelected, TSubclassOf<AActor>, ActorBP);

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
	
	void Build(ABuildingPlatform* dest, const float duration);

	UFUNCTION(BlueprintImplementableEvent, Category = "BuildingBot")
	void OnBuildBP(ABuildingPlatform* dest, const float duration);

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
	void BuildingSelected(TSubclassOf<AActor> actorBP);

	bool IsBusy = false;
};