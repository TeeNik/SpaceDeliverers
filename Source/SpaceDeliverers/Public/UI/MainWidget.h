#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class UProgressBar;
struct FGeometry;

UCLASS()
class SPACEDELIVERERS_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init(float value);
	void UpdateShield(float value);

	UFUNCTION(BlueprintImplementableEvent, Category = MainWidget)
	void ShowActionProgress(const float &seconds);

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, VisibleAnywhere)
	UProgressBar* ActionProgress;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	UProgressBar* ShieldBar;

private:

	float TargetPercent;
};
