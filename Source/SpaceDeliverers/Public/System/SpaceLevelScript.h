#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "SpaceLevelScript.generated.h"

class AShieldGenerator;

UCLASS(Blueprintable)
class SPACEDELIVERERS_API ASpaceLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	FORCEINLINE TArray<AShieldGenerator*> GetGenerators() { return Generators; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<AShieldGenerator*> Generators;

};
