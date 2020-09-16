// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GASPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class WIN_TESTSIDESCROLLER_API AGASPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:

    // Only called on the Client. Initialize ASC with Owner Actor and Avatar Actor
    virtual void AcknowledgePossession(APawn* P) override;
};
