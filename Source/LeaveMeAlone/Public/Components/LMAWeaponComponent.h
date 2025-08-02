// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAWeaponComponent.generated.h"

class ALMABaseWeapon;
class UAnimMontage;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMAWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

    UFUNCTION(BlueprintCallable)
    bool GetCurrentWeaponAmmo(FAmmoWeapon& AmmoWeapon) const;

	ULMAWeaponComponent();
	void Fire();
	void StopFire();
	void Reload();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<ALMABaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	UAnimMontage* ReloadMontage;

private:

    UPROPERTY()
	ALMABaseWeapon* Weapon = nullptr;

	bool AnimReloading = false;
	bool bIsFiring = false;

    void SpawnWeapon();
	void InitAnimNotify();

	void OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh);
	bool CanReload() const;

	UFUNCTION()
	void OnNeedReloadHandler();

	FTimerHandle FireTimerHandle;
	float FireRate = 0.1f;

	void FireTick();

		
};
