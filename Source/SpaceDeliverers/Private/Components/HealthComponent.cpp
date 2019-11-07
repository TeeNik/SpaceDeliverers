#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{

}

void UHealthComponent::TakeDamage(int damage)
{
	CurrentHealth -= damage;
	if (CurrentHealth <= 0) {
		
	}
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}
