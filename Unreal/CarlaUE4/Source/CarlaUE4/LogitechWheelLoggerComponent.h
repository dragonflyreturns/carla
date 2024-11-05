#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LogitechWheelLoggerComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CARLAUE4_API ULogitechWheelLoggerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Constructor
    ULogitechWheelLoggerComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Function to log data to a CSV file
    void LogDataToCSV();

    // Function to handle button press
    void OnButtonPressed();

private:
    // The count to be logged
    int32 Count;

    // File path for the CSV
    FString FilePath;

    // Function to set up input bindings
    void SetupInputBindings();
};
