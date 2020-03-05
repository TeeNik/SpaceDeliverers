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

	/*UPROPERTY(EditDefaultsOnly)
	FVector SpawnPoint;*/

	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* PreviewMaterial;

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* SpawnPoint;

private:
	AActor* previewActor = nullptr;
	
};
