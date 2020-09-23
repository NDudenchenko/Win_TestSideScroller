// Fill out your copyright notice in the Description page of Project Settings.


#include "GASGA_CharacterJump.h"
#include "GASCharacterBase.h"

UGASGA_CharacterJump::UGASGA_CharacterJump()
{
    AbilityInputID = EGASAbilityInputID::Jump;
    InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
    AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Jump")));
}

void UGASGA_CharacterJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    
    if(HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
    {
        if(!CommitAbility(Handle, ActorInfo, ActivationInfo))
        {
            EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
        }

        AGASCharacterBase* Character = CastChecked<AGASCharacterBase>(ActorInfo->AvatarActor.Get(), ECastCheckedType::NullAllowed);
        Character->Jump();
        UE_LOG(LogTemp, Display, TEXT("Jump ability cpp 2"));
    }
}

bool UGASGA_CharacterJump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
    const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
    if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
    {
        return false;
    }

    const AGASCharacterBase* Character = CastChecked<AGASCharacterBase>(ActorInfo->AvatarActor.Get(), ECastCheckedType::NullAllowed);
    return Character && Character->CanJump();
    
}

void UGASGA_CharacterJump::CancelAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         bool bReplicateCancelAbility)
{
    if (ScopeLockCount > 0)
    {
        WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGASGA_CharacterJump::CancelAbility, Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility));
        return;
    }
    
    Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

    ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
    Character->StopJumping();
}

void UGASGA_CharacterJump::InputReleased(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
    CancelAbility(Handle, ActorInfo, ActivationInfo, true);
}

