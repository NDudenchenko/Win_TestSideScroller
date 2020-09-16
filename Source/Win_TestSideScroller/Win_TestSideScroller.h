// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EGASAbilityInputID: uint8
{
    // 0 None
    None         UMETA(DisplayName="None"),
    
    // 1 Jump
     Jump        UMETA(DisplayName="Jump"),
    
    // 2 Sprint
    Sprint       UMETA(DisplayName="Sprint")
};

