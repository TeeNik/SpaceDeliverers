#include "InteractiveActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

AInteractiveActor::AInteractiveActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	RootComponent = Box;
	Mesh->SetupAttachment(Box);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetGenerateOverlapEvents(false);
	//Mesh->SetCustomDepthStencilValue(255);
	Mesh->CustomDepthStencilValue = 255;
	GLog->Log("Creating of AInteractiveActor: ");
}

void AInteractiveActor::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractiveActor::OnSelect(UInteractionComponent * interComp)
{
	Mesh->SetRenderCustomDepth(true);
}

void AInteractiveActor::OnDeselect()
{
	Mesh->SetRenderCustomDepth(false);
}
