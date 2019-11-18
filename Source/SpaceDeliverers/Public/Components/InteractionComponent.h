#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class AInstrument;
class IInteractive;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEDELIVERERS_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();

	FORCEINLINE const AInstrument* GetInstrument() { return Instrument; }
	FORCEINLINE void SetInstrument(AInstrument* instrument) { Instrument = instrument; }
	//FORCEINLINE const TScriptInterface<IInteractive> GetInteractive() { return Interactive; }
	//FORCEINLINE void SetInteractive(IInteractive* interactive) {/* Interactive = interactive;*/ }

	void OnFire();
	void OnSelect(IInteractive* interactive);
	void OnDeselect();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnEnterInventory();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	class AInstrument* Instrument;

	/*UPROPERTY()
	class TScriptInterface<IInteractive> Interactive;*/
		
};
