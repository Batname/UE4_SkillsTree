// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SkillComponent.h"
#include "SkillsTreeCharacter.generated.h"

UCLASS(config=Game)
class ASkillsTreeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ASkillsTreeCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


private:
	/** Return a fixed transform base on the given spring arm */
	FTransform GetFixedSpringArmTransform(USpringArmComponent* SpringArm);

	/** Return an array of transform in order to determine how many skills will get spawned */
	TArray<FTransform> GetSpawnTransforms(int32 level);

protected:
	/** The root component which the spring arm component will be attached */
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SkillsRootComp;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* LevelOneSpringArm;	

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* LevelTwoSpringArm;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* LevelThreeSpringArm;

	/** Skills Component reference */
	UPROPERTY(VisibleAnywhere)
	USkillComponent* SkillsComponent;

	/** Fires a skill */
	UFUNCTION(BlueprintCallable, Category = TLSkillsTree)
	void Fire(bool bShouldFireSecondary = false);
};

