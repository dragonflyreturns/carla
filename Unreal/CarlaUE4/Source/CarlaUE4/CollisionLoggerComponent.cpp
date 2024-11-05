#include "CollisionLoggerComponent.h"
#include "GameFramework/Actor.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"

// Sets default values for this component's properties
UCollisionLoggerComponent::UCollisionLoggerComponent()
{
    PrimaryComponentTick.bCanEverTick = false; // No need to tick every frame
}

// Called when the game starts
void UCollisionLoggerComponent::BeginPlay()
{
    Super::BeginPlay();

    // Initialize StartTime with the current time
    StartTime = FDateTime::Now();

    // Bind the collision event
    if (AActor* Owner = GetOwner())
    {
        Owner->OnActorHit.AddDynamic(this, &UCollisionLoggerComponent::OnCollision);
    }

    // Create CSV file with headers if it doesn't already exist
    FString FilePath = FPaths::ProjectDir() + TEXT("CollisionData.csv");
    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
    {
        FString Headers = TEXT("ElapsedTimeSeconds,ImpactPoint,ImpactNormal\n");
        FFileHelper::SaveStringToFile(Headers, *FilePath);
    }
}

// Handle collision events
void UCollisionLoggerComponent::OnCollision(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& HitResult)
{
    // Calculate elapsed time
    FTimespan ElapsedTime = FDateTime::Now() - StartTime;
    float ElapsedSeconds = ElapsedTime.GetTotalSeconds();

    // Log collision data
    LogToCSV(ElapsedSeconds, HitResult);
}

// Log collision data to CSV
void UCollisionLoggerComponent::LogToCSV(float ElapsedTime, const FHitResult& HitResult)
{
    FString FilePath = FPaths::ProjectDir() + TEXT("CollisionData.csv");
    FString CSVLine = FString::Printf(TEXT("%f,%s,%s\n"),
        ElapsedTime,
        *HitResult.ImpactPoint.ToString(),
        *HitResult.ImpactNormal.ToString());

    FFileHelper::SaveStringToFile(CSVLine, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);

    UE_LOG(LogTemp, Warning, TEXT("Collision logged: Elapsed Time: %f seconds, Impact Point: %s, Impact Normal: %s"),
        ElapsedTime,
        *HitResult.ImpactPoint.ToString(),
        *HitResult.ImpactNormal.ToString());
}
