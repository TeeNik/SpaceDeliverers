#include "ShieldGenerator.h"
#include "Instrument.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"

AShieldGenerator::AShieldGenerator() {
}

void AShieldGenerator::BeginPlay()
{
	CurrentEnergy = MaxEnergy;
}

void AShieldGenerator::Interact(class AInstrument *& inHand, class ACharacter* character) {
	UE_LOG(LogTemp, Log, TEXT("Interact"));
	if (inHand != NULL) {
		UE_LOG(LogTemp, Log, TEXT("inHand != NULL"));
		if (inHand->GetType() == InstrumentType::Wrench) {
			UE_LOG(LogTemp, Log, TEXT("inHand->GetType()"));
			if (CurrentEnergy < MaxEnergy) {
				UE_LOG(LogTemp, Log, TEXT("CurrentEnergy < MaxEnergy"));
				++CurrentEnergy;
				OnEnergyUpdate.Broadcast();
				UpdateMaterial();
			}
		}
	}
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