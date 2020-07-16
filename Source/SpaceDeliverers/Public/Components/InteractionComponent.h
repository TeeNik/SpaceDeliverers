#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class AInstrument;
class IInteractive;
enum InstrumentType;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInstrumentChanged, int32, type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInstrumentUsed, int32, type);


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEDELIVERERS_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();

	FORCEINLINE const AInstrument* GetInstrument() { return Instrument; }
	FORCEINLINE const IInteractive* GetInteractive() { return Interactive; }
	FORCEINLINE void SetInteractive(IInteractive* interactive) { Interactive = interactive; }

	void SetInstrument(AInstrument* instrument);
	void OnFire();
	void OnRelease();
	void OnSelect(IInteractive* interactive);
	void OnDeselect();

	UPROPERTY(BlueprintAssignable)
	FInstrumentChanged OnInstrumentChanged;

	UPROPERTY(BlueprintAssignable)
	FInstrumentUsed OnInstrumentUsed;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	AInstrument* Instrument;

	IInteractive* Interactive;
		
};
