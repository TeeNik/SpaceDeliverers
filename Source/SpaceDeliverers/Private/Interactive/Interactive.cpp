#include "Interactive.h"
#include "Components/StaticMeshComponent.h"

AInteractive::AInteractive()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

void AInteractive::OnSelect()
{
	GLog->Log("OnSelect");
	Mesh->SetRenderCustomDepth(true);
}

void AInteractive::OnDeselect()
{
	GLog->Log("OnDeselect");
	Mesh->SetRenderCustomDepth(false);
}
