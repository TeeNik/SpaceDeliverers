#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EnemySpawnManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEDELIVERERS_API UEnemySpawnManager : public USceneComponent
{
	GENERATED_BODY()

public:	
	UEnemySpawnManager();

protected:
	virtual void BeginPlay() override;
};
