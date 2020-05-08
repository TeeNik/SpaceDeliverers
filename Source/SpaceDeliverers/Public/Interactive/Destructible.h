#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Destructible.generated.h"

UINTERFACE(Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UDestructible : public UInterface
{
	GENERATED_BODY()
};

class IDestructible
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	virtual	void OnDestroyReached() {};

	UFUNCTION(BlueprintCallable)
	virtual	void OnCrashReached() { IsCrashed = true; };

	UFUNCTION(BlueprintCallable)
	virtual	void OnTargetReached() { IsTarget = true; };

	bool GetIsTarget() { return IsTarget; }
	bool GetIsCrashed() { return IsCrashed; }

protected:
	bool IsTarget;
	bool IsCrashed;
};
