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

	virtual void OnSelect() override;
	virtual void OnDeselect() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

};
