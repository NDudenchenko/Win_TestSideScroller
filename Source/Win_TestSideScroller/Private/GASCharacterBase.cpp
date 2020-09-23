// Fill out your copyright notice in the Description page of Project Settings.


#include "GASCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GASGameplayAbilityBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AGASCharacterBase::AGASCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("MyAbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	
	AttributeSet = CreateDefaultSubobject<UGASAttributeSetBase>(TEXT("MyAttributeSet"));
	//Test string 
}

// Called when the game starts or when spawned
void AGASCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMoveSpeedAttribute())
	//.AddUObject(this, &AGASCharacterBase::OnMovementAttributeChanged);

	AddCharacterAbilities();
}

// Called every frame
void AGASCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGASCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &AGASCharacterBase::MoveRight);

	// Bind player input to the AbilitySystemComponent
	GASInputBinding();
}

// Only called on the Server. Calls before Server's AcknowledgePossession.
// Initialize ASC with Owner Actor and Avatar Actor
void AGASCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	// ASC MixedMode replication requires that the ASC Owner's Owner be the Controller. 
	SetOwner(NewController);
}

UAbilitySystemComponent* AGASCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGASCharacterBase::AddCharacterAbilities()
{
	// Use if abilities store in TArray
	// for(TSubclassOf<UGASGameplayAbilityBase>& StartupAbility : CharacterAbilities)
	// {
	// 	AbilitySystemComponent->GiveAbility(
	// 		FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	//
	// }

	for(const auto& ability: CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(
            FGameplayAbilitySpec(ability.Value, 1, static_cast<int32>(ability.Key), this));
	}
}

void AGASCharacterBase::InitializeAttributes()
{
	// FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	// EffectContext.AddSourceObject(this);
	//
	// FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, GetCharacterLevel(), EffectContext);
	// if (NewHandle.IsValid())
	// {
	// 	FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	// }
}

void AGASCharacterBase::GASInputBinding() const
{
	/*AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(
		FString("ConfirmTarget"), FString("CancelTarget"), FString("EGASAbilityInputID"),
		static_cast<int32>(EGASAbilityInputID::Confirm), static_cast<int32>(EGASAbilityInputID::Cancel)));*/

	AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(
        FString("ConfirmTarget"), FString("CancelTarget"), FString("EGASAbilityInputID")));
}

void AGASCharacterBase::MoveRight(float value)
{
	AddMovementInput(FVector(0, -1, 0), value);
}
