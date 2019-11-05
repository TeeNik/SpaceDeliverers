#include "Interactive.h"
#include "Components/StaticMeshComponent.h"

AInteractive::AInteractive()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

void AInteractive::OnSelect()
{
	Mesh->SetRenderCustomDepth(true);
}

void AInteractive::OnDeselect()
{
	Mesh->SetRenderCustomDepth(false);
}
