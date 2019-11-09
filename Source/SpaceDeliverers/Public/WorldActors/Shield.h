#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shield.generated.h"

UCLASS()
class SPACEDELIVERERS_API AShield : public AActor
{
	GENERATED_BODY()
	
public:	
	AShield();

	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Instrument, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnShieldUpdate();

	UPROPERTY()
	TArray<class AShieldGenerator*> Generators;
};
