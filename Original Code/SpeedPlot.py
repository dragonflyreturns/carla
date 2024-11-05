import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV file
df = pd.read_csv('D:\\carla\\Original Code\\VehicleSpeedData.csv')

# Print column names to confirm the headers
print("Column names in CSV:", df.columns)

# If "Time" exists as a column, proceed
if 'ElapsedTimeSeconds' in df.columns:
    # Convert the 'Time' column to float
    df['ElapsedTimeSeconds'] = df['ElapsedTimeSeconds'].astype(float)
    df['Speed'] = df['Speed'].astype(float)

    # Plot Speed vs Time
    plt.plot(df['ElapsedTimeSeconds'], df['Speed'])
    plt.title('Speed vs Time')
    plt.xlabel('Time (seconds)')
    plt.ylabel('Speed (km/h)')
    plt.grid(True)
    plt.show()
else:
    print("The 'ElapsedTimeSeconds' column was not found. Check the CSV headers.")
