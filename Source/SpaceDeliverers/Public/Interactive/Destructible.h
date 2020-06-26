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

	//UFUNCTION(BlueprintCallable)
	virtual	void DestroyReached() {};

	//UFUNCTION(BlueprintCallable)
	virtual	void CrashReached() { IsCrashed = true; };

	//UFUNCTION(BlueprintCallable)
	virtual	void TargetReached() { IsTarget = true; };

	//UFUNCTION(BlueprintCallable)
	virtual	void TargetRelease() { IsTarget = false; };

	bool GetIsTarget() { return IsTarget; }
	bool GetIsCrashed() { return IsCrashed; }

protected:
	bool IsTarget;
	bool IsCrashed;
};
