// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Components/LMAHealthComponent.h"

ULMAHealthComponent::ULMAHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULMAHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &ULMAHealthComponent::OnTakeAnyDamage);
	}
}

void ULMAHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsDead()) return;
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}

bool ULMAHealthComponent::IsDead() const 
{
return Health <= 0.0f;
}

bool ULMAHealthComponent::IsHealthFull() const
{
return FMath::IsNearlyEqual(Health, MaxHealth);
}

bool ULMAHealthComponent::AddHealth(float NewHealth)
{
	if (IsDead() || IsHealthFull()) return false;
	Health = FMath::Clamp(Health+NewHealth, 0.0f, MaxHealth);
	return true;
}
