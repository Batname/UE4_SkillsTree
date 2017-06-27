// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skill.generated.h"

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	WaterBlob,
	FileBall
};

UCLASS()
class SKILLSTREE_API ASkill : public AActor
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpusle, const FHitResult& Hit);
	
public:	
	// Sets default values for this actor's properties
	ASkill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;
	
	/** Increease the level by one, clamp on max level */
	UFUNCTION(BlueprintCallable, Category = TLSkillsTree)
	void AdvanceLevel() { CurrentLevel + 1 > MaxLevel ? 1 : ++CurrentLevel; }

	/** reset the level of the skills - 0 that meens that the playes will not be able to fire */
	UFUNCTION(BlueprintCallable, Category = TLSkillsTree)
	void ResetLevel() { CurrentLevel = 0; }

	/** Return the level of current skill */
	UFUNCTION(BlueprintCallable, Category = TLSkillsTree)
	UTexture* GetSkillTexture() { return SkillTexture; }

	/** Return skill type */
	ESkillType GetSkillType() { return SkillType; }

	/** Return true if the level is maxed out */
	bool IsMaxLevel() { return CurrentLevel == MaxLevel; }

private:
	int32 CurrentLevel = 1;
	int32 MaxLevel = 3;

protected:
	/** Sphere comp used for collision */
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComp;

	/** This component is used to simulate the movement of our skill */
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComp;

	/** The Particle comp which emits the active particle system */
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* ParticleComp;

	/** The paticle system for our projectible when traveling */
	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* ProjectileFX;

	/** The particle system for collision */
	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* ProjectileCollisionFX;

	/** The skill texture */
	UPROPERTY(EditDefaultsOnly)
	class UTexture* SkillTexture;

	/** The time that our skill will get destroyed */
	UPROPERTY(EditAnywhere)
	float DestroyDelay = 1.5f;

	/** The skill type of the skill */
	UPROPERTY(EditDefaultsOnly)
	ESkillType SkillType;
};

