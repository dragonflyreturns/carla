#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollisionLoggerComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CARLAUE4_API UCollisionLoggerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UCollisionLoggerComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    // To store the start time
    FDateTime StartTime;

    // Function to handle collision events
    UFUNCTION()
        void OnCollision(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& HitResult);

    // Function to log data to CSV
    void LogToCSV(float ElapsedTime, const FHitResult& HitResult);
};
