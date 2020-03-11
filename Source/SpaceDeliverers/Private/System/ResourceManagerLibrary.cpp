#include "ResourceManagerLibrary.h"
#include "Resources/ResourceManagerSingleton.h"
#include "Engine.h"

UResourceManagerSingleton* UResourceManagerLibrary::GetData()
{
	UResourceManagerSingleton* data = Cast<UResourceManagerSingleton>(GEngine->GameSingleton);
	if (!data) return NULL;
	if (!data->IsValidLowLevel()) return NULL;
	return data;
}