// Fill out your copyright notice in the Description page of Project Settings.


#include "GASPlayerControllerBase.h"

#include "GASCharacterBase.h"

// Only called on the Client. Initialize ASC with Owner Actor and Avatar Actor
void AGASPlayerControllerBase::AcknowledgePossession(APawn* P)
{
    Super::AcknowledgePossession(P);

    AGASCharacterBase* CharacterBase = Cast<AGASCharacterBase>(P);
    if(CharacterBase)
    {
        CharacterBase->GetAbilitySystemComponent()->InitAbilityActorInfo(CharacterBase, CharacterBase);
    }
}
