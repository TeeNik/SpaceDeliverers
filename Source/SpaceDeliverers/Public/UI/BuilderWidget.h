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

protected:
	UPROPERTY(meta = (BindWidget), VisibleAnywhere, BlueprintReadWrite)
	UButton* TurretButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

private:
	FBuildingSelected OnBuildingSelected;
	
	UFUNCTION()
	void OnTurretButtonClicked();

	UFUNCTION()
	void CloseWidget();
};
