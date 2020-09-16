// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GASAttributeSetBase.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class WIN_TESTSIDESCROLLER_API UGASAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:

	// Current Health, when 0 we expect owner to die unless prevented by an ability. Capped by MaxHealth.
	// Positive changes can directly use this.
	// Negative changes to Health should go through Damage meta attribute.
	UPROPERTY(BlueprintReadOnly, Category="Health" /*, ReplicatedUsing = OnRep_Health*/)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, Health)

	// MaxHealth is its own attribute since GameplayEffects may modify it
	UPROPERTY(BlueprintReadOnly, Category="Health" /*, ReplicatedUsing = OnRep_MaxHealth*/)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, MaxHealth)

	// MoveSpeed affects how fast characters can move.
	UPROPERTY(BlueprintReadOnly, Category="MoveSpeed" /*, ReplicatedUsing = OnRep_MoveSpeed*/)
	FGameplayAttributeData MoveSpeed = 600.0f;
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, MoveSpeed)

	// How far character can jump upward
	UPROPERTY(BlueprintReadOnly, Category="JumpHeight" /*, ReplicatedUsing = OnRep_JumpHeight*/)
	FGameplayAttributeData JumpHeight = 800.0f;
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, JumpHeight)

protected:

	/**
	* These OnRep functions exist to make sure that the ability system internal representations are synchronized properly during replication
	**/

	// UFUNCTION()
	// virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	//
	// UFUNCTION()
 //    virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
 //
	// UFUNCTION()
 //    virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed);
 //
	// UFUNCTION()
 //    virtual void OnRep_JumpHeight(const FGameplayAttributeData& OldJumpHeight);
};
