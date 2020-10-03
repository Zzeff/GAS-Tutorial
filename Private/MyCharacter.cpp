// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

AMyCharacter::AMyCharacter(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	// Create ability system component, and set it to be explicitly replicated
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystem->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AbilitySystem->SetIsReplicated(true);
}

//Atrribute Functions
void AMyCharacter::InitializeAttributes()
{
	if (HasAuthority() && AttributeSet)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attributes Initialized"));
		// Can run on Server and Client
		FGameplayEffectContextHandle EffectContext = AbilitySystem->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = AbilitySystem->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystem->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystem);
		}
	}
}