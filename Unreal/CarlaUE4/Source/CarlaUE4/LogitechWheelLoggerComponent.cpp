#include "LogitechWheelLoggerComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Engine/Engine.h"

ULogitechWheelLoggerComponent::ULogitechWheelLoggerComponent()
{
    PrimaryComponentTick.bCanEverTick = false; // Disable ticking as it's not needed
    Count = 0;
    FilePath = FPaths::ProjectDir() + TEXT("LogData.csv");
}

void ULogitechWheelLoggerComponent::BeginPlay()
{
    Super::BeginPlay();
    SetupInputBindings();
}

void ULogitechWheelLoggerComponent::SetupInputBindings()
{
    // Get the player controller and bind input
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        // Bind the action to the "Logitech Wheel Face Button Top"
        // You must set up this input action in the Input settings in Unreal Engine
        PlayerController->InputComponent->BindAction("LogitechWheelButtonTop", IE_Pressed, this, &ULogitechWheelLoggerComponent::OnButtonPressed);
    }
}

void ULogitechWheelLoggerComponent::OnButtonPressed()
{
    // Increment the count and log it
    Count++;
    LogDataToCSV();
}

void ULogitechWheelLoggerComponent::LogDataToCSV()
{
    FString LogEntry = FString::Printf(TEXT("%d\n"), Count);

    // Append the count to the CSV file
    FFileHelper::SaveStringToFile(LogEntry, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);

    // Log to the output log for debugging
    UE_LOG(LogTemp, Log, TEXT("Button pressed. Count: %d"), Count);
}
