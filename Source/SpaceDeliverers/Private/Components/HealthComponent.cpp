#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{

}

void UHealthComponent::TakeDamage(int damage)
{
	GLog->Log("CurrentHealth: " + FString::FromInt(CurrentHealth)+ " Damage: " + FString::FromInt(damage));
	CurrentHealth -= damage;
	OnTakeDamage.Broadcast(CurrentHealth, this);
	if (CurrentHealth <= 0) {
		OnDeath.Broadcast(this);
	}
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	GLog->Log("MaxHealth: " + FString::FromInt(MaxHealth) + " CurrentHealth: " + FString::FromInt(CurrentHealth));
}
