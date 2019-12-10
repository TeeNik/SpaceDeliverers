#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "SpaceLevelScript.generated.h"

class AShieldGenerator;
class AShield;

UCLASS(Blueprintable)
class SPACEDELIVERERS_API ASpaceLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	FORCEINLINE TArray<AShieldGenerator*>& GetGenerators() { return Generators; }
	FORCEINLINE AShield* GetShield() { return Shield; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<AShieldGenerator*> Generators;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	AShield* Shield;

};
