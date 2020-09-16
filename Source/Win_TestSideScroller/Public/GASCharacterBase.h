// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GASAttributeSetBase.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GASGA_CharacterJump.h"

#include "GASCharacterBase.generated.h"

UCLASS()
class WIN_TESTSIDESCROLLER_API AGASCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	
public:
	// Sets default values for this character's properties
	AGASCharacterBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Only called on the Server. Calls before Server's AcknowledgePossession.
	// Initialize ASC with Owner Actor and Avatar Actor
	virtual void PossessedBy(AController* NewController) override;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UGASAttributeSetBase* AttributeSet;

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Abilities")
	//TArray<TSubclassOf<class UGASGameplayAbilityBase>> CharacterAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="GAS|Abilities")
	TMap<EGASAbilityInputID, TSubclassOf<UGASGameplayAbilityBase>> CharacterAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void AddCharacterAbilities();

	virtual void InitializeAttributes();
	
	void  GASInputBinding() const;

	void MoveRight(float value);
};
