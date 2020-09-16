// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility.h"
#include "Win_TestSideScroller.h"
#include "GASGameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class WIN_TESTSIDESCROLLER_API UGASGameplayAbilityBase : public UGameplayAbility
{
    GENERATED_BODY()
public:
	UGASGameplayAbilityBase();

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
    EGASAbilityInputID AbilityInputID = EGASAbilityInputID::None;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
    EGASAbilityInputID AbilityID = EGASAbilityInputID::None;
};
