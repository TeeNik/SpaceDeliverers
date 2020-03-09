#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterAnimComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEDELIVERERS_API UCharacterAnimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterAnimComponent();

protected:
	virtual void BeginPlay() override;
};
