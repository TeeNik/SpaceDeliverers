#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class UProgressBar;

UCLASS()
class SPACEDELIVERERS_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ShieldBar;


};
