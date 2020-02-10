#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Instrument.generated.h"

UENUM(Blueprintable)
enum InstrumentType {
	None,
	Wrench,
	Gun,
	Builder,
};

UCLASS()
class SPACEDELIVERERS_API AInstrument : public AActor
{
	GENERATED_BODY()
	
public:	
	AInstrument();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Instrument, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

public:
	virtual void Use();
	virtual InstrumentType GetType() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Instrument")
	void Release();

};
