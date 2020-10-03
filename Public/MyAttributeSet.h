// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 *
 */
UCLASS()
class PROJECTALPHA_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	// Constructor and overrides
	UMyAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//Declaring Character Stats

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Health)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxHealth, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxHealth)

	//needed to store attributes during calculations
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData OldValue;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, OldValue)

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/** Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes. (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before) */
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);


protected:
	
	//Replicated attribute functions
	UFUNCTION()
		virtual void OnRep_Health();

	UFUNCTION()
		virtual void OnRep_MaxHealth();


};
