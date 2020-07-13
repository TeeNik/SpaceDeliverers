#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactive.h"
#include "InteractiveActor.generated.h"

UCLASS()
class SPACEDELIVERERS_API AInteractiveActor : public AActor, public IInteractive
{
	GENERATED_BODY()
	
public:	
	AInteractiveActor();

	virtual void OnSelect(class UInteractionComponent* interComp) override;
	virtual void OnDeselect() override;

	virtual float GetInteractionTime() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float InteractionTime;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	//class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Box;

};
