#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactive.h"
#include "Toolbox.generated.h"


UCLASS()
class SPACEDELIVERERS_API AToolbox : public AActor, public IInteractive
{
	GENERATED_BODY()
	
public:	
	AToolbox();

	void Interact(class AInstrument*& inHand, const class ACharacter* character) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AWrench> WrenchBase;
};
