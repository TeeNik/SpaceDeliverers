#include "ShieldGenerator.h"
#include "Instrument.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"
#include "InteractionComponent.h"

AShieldGenerator::AShieldGenerator() {

	Part1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Part1"));
	Part2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Part2"));
	Part1->SetupAttachment(RootComponent);
	Part2->SetupAttachment(RootComponent);
}

void AShieldGenerator::BeginPlay()
{
	Super::BeginPlay();
	CurrentEnergy = MaxEnergy;
	Part1->SetCustomDepthStencilValue(255);
	Part2->SetCustomDepthStencilValue(255);
}

void AShieldGenerator::OnSelect(UInteractionComponent* interComp)
{
	Mesh->SetRenderCustomDepth(true);
	Part1->SetRenderCustomDepth(true);
	Part2->SetRenderCustomDepth(true);
}

void AShieldGenerator::OnDeselect()
{
	Mesh->SetRenderCustomDepth(false);
	Part1->SetRenderCustomDepth(false);
	Part2->SetRenderCustomDepth(false);
}

bool AShieldGenerator::Interact(class UInteractionComponent* interComp, class ACharacter* character) {
	const AInstrument* inHand = interComp->GetInstrument();
	if (inHand != NULL) {
		if (inHand->GetType() == InstrumentType::Wrench) {
			if (CurrentEnergy < MaxEnergy) {
				OnInteractBP();
				return true;
			}
		}
	}
	return false;
}

void AShieldGenerator::IncreaseEnergy()
{
	++CurrentEnergy;
	OnEnergyUpdate.Broadcast();
	UpdateMaterial();
}

void AShieldGenerator::UpdateMaterial()
{
	const int matIndex = 2;
	UMaterialInterface * Material = Mesh->GetMaterial(matIndex);
	UMaterialInstanceDynamic* matInstance = Mesh->CreateDynamicMaterialInstance(matIndex, Material);
	//FColor color = FColor::MakeRandomColor();
	float x = CurrentEnergy / (float)MaxEnergy;
	FColor color = FColor(2 * x * 255, 2 * (1 - x) * 255, 0);
	if (matInstance != nullptr)
	{
		matInstance->SetVectorParameterValue("Color", color);
	}
}

void AShieldGenerator::ReduceEnergy()
{
	--CurrentEnergy;
}