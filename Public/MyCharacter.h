// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "MyAttributeSet.h"
#include "MyCharacter.generated.h"


class UGameplayAbility;
class UGameplayEffect;

/**
 *
 */
UCLASS()
class PROJECTALPHA_API AMyCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
		class UAbilitySystemComponent* AbilitySystem;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystem;
	};


	UPROPERTY()
		UMyAttributeSet* AttributeSet;


	// Default attributes for a character for initializing on spawn/respawn.
// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	virtual void InitializeAttributes();

};