import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file
file_path = 'D:\carla\Original Code\RotationData.csv'  # Ensure this path matches your CSV file location
data = pd.read_csv(file_path)

# Extract time and rotation values
time = data['ElapsedTimeSeconds']  # Time in seconds
yaw = data['YawRotation']  # Yaw rotation values
pitch = data['PitchRotation']  # Pitch rotation values
roll = data['RollRotation']  # Roll rotation values

# Plot Yaw, Pitch, and Roll vs. Time
plt.figure(figsize=(10, 6))

# Plot Yaw rotation
plt.plot(time, yaw, label='Yaw Rotation', color='blue')

# Plot Pitch rotation
#plt.plot(time, pitch, label='Pitch Rotation', color='green')

# Plot Roll rotation
#plt.plot(time, roll, label='Roll Rotation', color='red')

# Add labels and legend
plt.xlabel('Time (s)')
plt.ylabel('Rotation (degrees)')
plt.title('Rotation vs Time')
plt.legend()
plt.grid(True)

# Display the plot
plt.show()
