#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ResourceManagerLibrary.generated.h"

class UResourceManagerSingleton;

UCLASS()
class SPACEDELIVERERS_API UResourceManagerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "ResourceManagerLibrary")
	static UResourceManagerSingleton* GetData();
	
};
