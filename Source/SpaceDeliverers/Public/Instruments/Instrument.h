#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Instrument.generated.h"

UENUM()
enum class InstrumentType {
	None,
	Wrench,
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
};
