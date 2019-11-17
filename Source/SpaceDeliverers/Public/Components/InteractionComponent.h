#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class AInstrument;
class AInteractive;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEDELIVERERS_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();

	FORCEINLINE const AInstrument* GetInstrument() { return Instrument; }
	FORCEINLINE void SetInstrument(AInstrument* instrument) { Instrument = instrument; }
	FORCEINLINE const AInteractive* GetInteractive() { return Interactive; }
	FORCEINLINE void SetInteractive(AInteractive* interactive) { Interactive = interactive; }

	void OnFire();
	void OnSelect(AInteractive* interactive);
	void OnDeselect();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnEnterInventory();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	class AInstrument* Instrument;

	UPROPERTY()
	class TScriptInterface<AInteractive> Interactive;
		
};
