// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "ParticleDefinitions.h"


// Sets default values
ASkill::ASkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    SphereComp->SetCollisionProfileName(FName("BlockAll"));
    SetRootComponent(SphereComp);

    // Initialize the movement component and its properties
    ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComp"));
    ProjectileMovementComp->ProjectileGravityScale = 0.f;
    ProjectileMovementComp->InitialSpeed = 3000.0f;

    ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(FName("ParticleComp"));
    ParticleComp->SetupAttachment(SphereComp);
}

// Called when the game starts or when spawned
void ASkill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASkill::OnConstruction(const FTransform& Transform)
{

    Super::OnConstruction(Transform);
    // TODO add implementation
}

void ASkill::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpusle, const FHitResult& Hit)
{
    if (ProjectileCollisionFX)
    {
        // Activate the collision fx and start the destroy timer
        ParticleComp->SetTemplate(ProjectileCollisionFX);
        ParticleComp->Activate(true);

        FTimerHandle TimerHandle;
        FTimerDelegate TimerDel;

        TimerDel.BindLambda([&]()
        {
            Destroy();
        });

        GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, DestroyDelay, false);
    }
}
