#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ResourceManagerSingleton.generated.h"

class UDataTable;

UCLASS(Blueprintable)
class SPACEDELIVERERS_API UResourceManagerSingleton : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Manager")
	UDataTable* BuildingDataTable;
};