#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class UProgressBar;

UCLASS()
class SPACEDELIVERERS_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateShield(const float& value);

	UFUNCTION(BlueprintImplementableEvent, Category = MainWidget)
	void ShowActionProgress(const float &seconds);

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, VisibleAnywhere)
	UProgressBar* ActionProgress;

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ShieldBar;

};
