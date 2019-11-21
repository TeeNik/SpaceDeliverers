#include "InteractiveActor.h"
#include "Components/StaticMeshComponent.h"

AInteractiveActor::AInteractiveActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

void AInteractiveActor::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractiveActor::OnSelect()
{ 
	Mesh->SetRenderCustomDepth(true);
}

void AInteractiveActor::OnDeselect()
{
	Mesh->SetRenderCustomDepth(false);
}
