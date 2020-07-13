#include "InteractiveActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

AInteractiveActor::AInteractiveActor()
{
	//Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	//RootComponent = Root;
	//Box->SetupAttachment(Root);
	//Mesh->SetupAttachment(Root);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetGenerateOverlapEvents(false);
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
