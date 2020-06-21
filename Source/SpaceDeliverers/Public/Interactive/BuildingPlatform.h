#pragma once

#include "CoreMinimal.h"
#include "Interactive/InteractiveActor.h"
#include "BuildingPlatform.generated.h"

UCLASS()
class SPACEDELIVERERS_API ABuildingPlatform : public AInteractiveActor
{
	GENERATED_BODY()

public:
	ABuildingPlatform();

	virtual void OnSelect(class UInteractionComponent * interComp) override;
	virtual void OnDeselect() override;
	virtual bool Interact(class UInteractionComponent* interComp, class ACharacter* character) override;

	inline bool IsFree() { return PlacedActor == nullptr; }
	inline bool GetIsBuildingProcess() { return IsBuildingProcess; }
	
	bool IsBotTarget;

	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* PreviewMaterial;

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* SpawnPoint;

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool IsBuildingProcess;

private:
	AActor* PreviewActor = nullptr;
	AActor* PlacedActor = nullptr;
};
