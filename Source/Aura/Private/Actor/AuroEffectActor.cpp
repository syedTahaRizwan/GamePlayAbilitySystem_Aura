// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuroEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values
AAuroEffectActor::AAuroEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}


// Called when the game starts or when spawned
void AAuroEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

void AAuroEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);
	

	//Make Effect Context
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext(); //Wrapper that holds the data members that stores the actual struct 
	EffectContextHandle.AddSourceObject(this);
	//Make Gameplayeffect Spec
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);

	//apply gameplay effect
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

}

