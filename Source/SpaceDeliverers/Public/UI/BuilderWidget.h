#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

//TODO replace by class
#include "BuildingBot.h"

#include "BuilderWidget.generated.h"

class UButton;


UCLASS()
class SPACEDELIVERERS_API UBuilderWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(FBuildingSelected& onBuildingSelected);

	void ShowWidget();

private:

	FBuildingSelected OnBuildingSelected;

	UPROPERTY(meta = (BindWidget))
	UButton* TurretButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;
	
	UFUNCTION()
	void OnTurretButtonClicked();

	UFUNCTION()
	void CloseWidget();
};
