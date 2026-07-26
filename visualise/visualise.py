import pandas as pd
import matplotlib.pyplot as plt

# 1. Load Simulation Data from CSV
csv_path = "data/simulation_output.csv"
try:
    df = pd.read_csv(csv_path)
    
    # CRITICAL FIX: Sort data by time to prevent zigzag line artifacts
    df = df.sort_values(by='Time').reset_index(drop=True)
    
    # Filter out invalid negative time steps if present
    df = df[df['Time'] >= 0]
    print("[INFO] Simulation data successfully loaded and sorted.")
except Exception as e:
    print(f"[ERROR] Failed to read simulation CSV file: {e}")
    exit()

# 2. Configure Dark Theme Dashboard Style
plt.style.use('dark_background')
fig, axs = plt.subplots(2, 2, figsize=(14, 9), facecolor='#0f172a')
fig.suptitle("YTÜ GNC SIMULATION — 6-DOF IMU & LOW-PASS FILTER ANALYSIS DASHBOARD", 
             fontsize=15, fontweight='bold', color='white', y=0.98)

# Color Palette Definitions
c_real = '#38bdf8'   # Sky Blue (Ground Truth / Physics)
c_meas = '#ef4444'   # Coral Red (Raw Sensor / Noise)
c_filt = '#22c55e'   # Emerald Green (Filtered Signal / LPF)
c_purple = '#a855f7' # Lavender (Integrated Position)
c_yellow = '#eab308' # Amber Yellow (Orientation Angle)

# --- PANEL 1: Accelerometer Z-Axis (Translational Domain) ---
axs[0, 0].set_facecolor('#1e293b')
axs[0, 0].scatter(df['Time'], df['Meas_Acc_Z'], color=c_meas, alpha=0.35, s=8, label='Raw Sensor (Meas Acc Z)')
axs[0, 0].plot(df['Time'], df['Real_Acc_Z'], color=c_real, linewidth=2, label='Ground Truth (Real Acc Z)')
axs[0, 0].plot(df['Time'], df['Filt_Acc_Z'], color=c_filt, linewidth=2, label='Filtered (Filt Acc Z - LPF)')
axs[0, 0].set_title("Accelerometer Z-Axis [m/s²]", color='white', fontsize=12, fontweight='bold', pad=10)
axs[0, 0].set_xlabel("Time [s]", color='#94a3b8')
axs[0, 0].set_ylabel("Acceleration [m/s²]", color='#94a3b8')
axs[0, 0].legend(loc='upper right', facecolor='#0f172a', edgecolor='#334155')
axs[0, 0].grid(True, linestyle='--', alpha=0.25)

# --- PANEL 2: Gyroscope Y-Axis Pitch Rate (Rotational Domain) ---
axs[0, 1].set_facecolor('#1e293b')
axs[0, 1].scatter(df['Time'], df['Meas_AngVel_Y'], color='#f97316', alpha=0.35, s=8, label='Raw Gyro (Meas AngVel Y)')
axs[0, 1].plot(df['Time'], df['Real_AngVel_Y'], color=c_real, linewidth=2, label='Ground Truth (Real AngVel Y)')
axs[0, 1].plot(df['Time'], df['Filt_AngVel_Y'], color=c_filt, linewidth=2, label='Filtered (Filt AngVel Y - LPF)')
axs[0, 1].set_title("Gyroscope Pitch Rate (Y-Axis) [rad/s]", color='white', fontsize=12, fontweight='bold', pad=10)
axs[0, 1].set_xlabel("Time [s]", color='#94a3b8')
axs[0, 1].set_ylabel("Angular Velocity [rad/s]", color='#94a3b8')
axs[0, 1].legend(loc='upper right', facecolor='#0f172a', edgecolor='#334155')
axs[0, 1].grid(True, linestyle='--', alpha=0.25)

# --- PANEL 3: Rocket Altitude / Position Z ---
axs[1, 0].set_facecolor('#1e293b')
axs[1, 0].plot(df['Time'], df['Real_Pos_Z'], color=c_real, linewidth=2.5, label='Ground Truth (Real Altitude)')
axs[1, 0].plot(df['Time'], df['Filt_Pos_Z'], color=c_purple, linestyle='--', linewidth=2, label='Integrated Filtered Altitude')
axs[1, 0].set_title("Rocket Altitude Ascent Curve (Position Z) [m]", color='white', fontsize=12, fontweight='bold', pad=10)
axs[1, 0].set_xlabel("Time [s]", color='#94a3b8')
axs[1, 0].set_ylabel("Altitude [m]", color='#94a3b8')
axs[1, 0].legend(loc='upper left', facecolor='#0f172a', edgecolor='#334155')
axs[1, 0].grid(True, linestyle='--', alpha=0.25)

# --- PANEL 4: Pitch Angle / Orientation (Theta Y) ---
axs[1, 1].set_facecolor('#1e293b')
axs[1, 1].plot(df['Time'], df['Real_Theta_Y'], color=c_real, linewidth=2.5, label='Ground Truth Pitch (Real Theta Y)')
axs[1, 1].plot(df['Time'], df['Filt_Theta_Y'], color=c_yellow, linestyle='--', linewidth=2, label='Integrated Filtered Pitch')
axs[1, 1].set_title("Orientation Angle (Pitch Angle - Theta Y) [rad]", color='white', fontsize=12, fontweight='bold', pad=10)
axs[1, 1].set_xlabel("Time [s]", color='#94a3b8')
axs[1, 1].set_ylabel("Angle [rad]", color='#94a3b8')
axs[1, 1].legend(loc='upper left', facecolor='#0f172a', edgecolor='#334155')
axs[1, 1].grid(True, linestyle='--', alpha=0.25)

plt.tight_layout(rect=[0, 0, 1, 0.96])
plt.savefig("data/gnc_simulation_dashboard.png", dpi=300, bbox_inches='tight')
plt.show()