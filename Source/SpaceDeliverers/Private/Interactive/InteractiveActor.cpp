#include "InteractiveActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

AInteractiveActor::AInteractiveActor()
{
	//Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	//Box->SetupAttachment(Root);
	//Mesh->SetupAttachment(Root);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetGenerateOverlapEvents(false);
	Mesh->SetupAttachment(RootComponent);
}

void AInteractiveActor::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetCustomDepthStencilValue(255);
}

void AInteractiveActor::OnSelect(UInteractionComponent * interComp)
{
	Mesh->SetRenderCustomDepth(true);
}

void AInteractiveActor::OnDeselect()
{
	Mesh->SetRenderCustomDepth(false);
}

float AInteractiveActor::GetInteractionTime()
{
	return InteractionTime;
}
