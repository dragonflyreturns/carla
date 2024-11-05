#include "GetSpeedActorComponent.h"
#include "GameFramework/Actor.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "Carla/Vehicle/CarlaWheeledVehicle.h"

// Sets default values for this component's properties
UGetSpeedActorComponent::UGetSpeedActorComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGetSpeedActorComponent::BeginPlay()
{
    Super::BeginPlay();

    // Initialize StartTime with the current time
    StartTime = FDateTime::Now();

    // Create CSV file with headers if it doesn't already exist
    FString FilePath = FPaths::ProjectDir() + TEXT("VehicleSpeedData.csv");
    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
    {
        FString Headers = TEXT("Speed,ElapsedTimeSeconds\n");
        FFileHelper::SaveStringToFile(Headers, *FilePath);
    }
}

// Called every frame
void UGetSpeedActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* Owner = GetOwner();
    if (Owner && Owner->IsA<ACarlaWheeledVehicle>())
    {
        ACarlaWheeledVehicle* Vehicle = Cast<ACarlaWheeledVehicle>(Owner);

        // Use GetRootComponent()->GetComponentVelocity() to get velocity
        FVector Velocity = Vehicle->GetRootComponent()->GetComponentVelocity();

        // Calculate speed in km/h
        float SpeedKmh = Velocity.Size() * 0.036f;

        // Calculate elapsed time in seconds
        FTimespan ElapsedTime = FDateTime::Now() - StartTime;
        float ElapsedSeconds = ElapsedTime.GetTotalSeconds();

        // Append data to CSV
        FString FilePath = FPaths::ProjectDir() + TEXT("VehicleSpeedData.csv");
        FString CSVLine = FString::Printf(TEXT("%f,%f\n"), SpeedKmh, ElapsedSeconds);
        FFileHelper::SaveStringToFile(CSVLine, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);

        UE_LOG(LogTemp, Warning, TEXT("Speed: %f km/h, Elapsed Time: %f seconds"), SpeedKmh, ElapsedSeconds);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No vehicle found or not of type ACarlaWheeledVehicle."));
    }
}
