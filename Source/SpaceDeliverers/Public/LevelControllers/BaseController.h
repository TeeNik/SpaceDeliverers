#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BaseController.generated.h"

class UUserWidget;
class UMainWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEDELIVERERS_API UBaseController : public USceneComponent
{
	GENERATED_BODY()

public:	
	UBaseController();

	FORCEINLINE int GetHealth() { return Health; }
	FORCEINLINE int GetShield() { return Shield; }
	FORCEINLINE UMainWidget* GetMainWidget() { return MainWidget; }

	void Initialize();
	void TakeDamage(const int& damage);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainWidgetBP;

	UPROPERTY()
	UMainWidget* MainWidget;

private:

	int Shield;
	int Health;

	UFUNCTION()
	void OnShieldUpdate(float value);


};
