#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class AInstrument;
class IInteractive;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEDELIVERERS_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();

	FORCEINLINE const AInstrument* GetInstrument() { return Instrument; }
	FORCEINLINE void SetInstrument(AInstrument* instrument) { Instrument = instrument; }
	FORCEINLINE const IInteractive* GetInteractive() { return Interactive; }
	FORCEINLINE void SetInteractive(IInteractive* interactive) { Interactive = interactive; }

	void OnFire();
	void OnRelease();
	void OnSelect(IInteractive* interactive);
	void OnDeselect();

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void OnEnterInventory();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	class AInstrument* Instrument;

	class IInteractive* Interactive;
		
};
