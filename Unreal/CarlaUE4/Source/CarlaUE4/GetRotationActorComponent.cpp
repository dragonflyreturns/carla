// Copyright (c) 2017 Computer Vision Center (CVC) at the Universitat Autonoma de Barcelona (UAB). This work is licensed under the terms of the MIT license. For a copy, see <https://opensource.org/licenses/MIT>.


#include "GetRotationActorComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"  // Include the HMD library
#include "GameFramework/Actor.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"

// Sets default values for this component's properties
UGetRotationActorComponent::UGetRotationActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Global variable to store the start time
FDateTime StartTime;

// Called when the game starts
void UGetRotationActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// Record the start time
	StartTime = FDateTime::Now();

	// Ensure the CSV file is created with headers
	FString FilePath = FPaths::ProjectDir() + TEXT("RotationData.csv");
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		// Write headers to the CSV file
		FString Headers = TEXT("YawRotation,PitchRotation,RollRotation,ElapsedTimeSeconds\n");
		FFileHelper::SaveStringToFile(Headers, *FilePath);
	}
}

// Called every frame
void UGetRotationActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Initialize variables for position and rotation
	FVector Position;
	FRotator Rotation;

	// Check if the HMD is connected and tracking
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		// Get the current position and rotation of the HMD
		UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(Rotation, Position);

		// Extract the Y-axis (Yaw) rotation
		float YawRotation = Rotation.Yaw;
		float PitchRotation = Rotation.Pitch;
		float RollRotation = Rotation.Roll;

		// Calculate elapsed time in seconds since StartTime
		float ElapsedTimeSeconds = (FDateTime::Now() - StartTime).GetTotalSeconds();

		// Log the Yaw rotation to the output log for debugging
		UE_LOG(LogTemp, Warning, TEXT("HMD Yaw Rotation: %f, HMD Pitch Rotation: %f, HMD Roll Rotation: %f, Time: %f"), YawRotation, PitchRotation, RollRotation, ElapsedTimeSeconds);

		// Create a CSV line with Yaw rotation and timestamp
		FString CSVLine = FString::Printf(TEXT("%f,%f,%f,%f\n"), YawRotation, PitchRotation, RollRotation, ElapsedTimeSeconds);

		// File path for CSV
		FString FilePath = FPaths::ProjectDir() + TEXT("RotationData.csv");

		// Append the CSV line to the file
		FFileHelper::SaveStringToFile(CSVLine, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HMD is not enabled or not tracking."));
	}
}