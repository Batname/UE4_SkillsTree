// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skill.h"
#include "SkillsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKILLSTREE_API USkillsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    /** An array which contains all the available skills */
    UPROPERTY(EditAnywhere)
    TArray<TSubclassOf<ASkill>> SkillsArray;

    /** Return the texture of the given skill's index, searching SkillsArray */
    UFUNCTION(BlueprintCallable, Category = TLSkillTree)
    UTexture* GetSkillTexture(int32 SkillNum);

    UFUNCTION(BlueprintCallable, Category = TLSkillTree)
    int32 GetSkillLevel(int32 SkillNum);

    /** Return the first mathing skill from SkillsArray */
    UFUNCTION(BlueprintCallable, Category = TLSkillTree)
    ASkill* GetSkillByType(ESkillType SkillType);

private:
    /** The Available skill pointes which can be spent in total */
    int32 AvailableSkillPoints;
    
public:
    /* Returns the new level of the skill */
    UFUNCTION(BlueprintCallable, Category = TLSkillTree)
    int32 AdvanceSkillLevel(ASkill* SkillToLevelUp);

    /** Reset the skill points and unlearns all the skill */
    UFUNCTION(BlueprintCallable, Category = TLSkillTree)
    void ResetSkillPoints();

protected:
    /** The amount of available skill points when starting the game */
    UPROPERTY(EditAnywhere)
    int32 InitialAvailableSkillsPoints;
};
