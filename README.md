# 🚀 6-DOF Rocket SITL Simulation & GNC Sensor Filtering

A C++ Software-in-the-Loop (SITL) 6-Degree-of-Freedom (6-DOF) flight dynamics simulation paired with a Python telemetry/GNC visualization dashboard.

This project simulates real-world rocket dynamics including dynamic mass depletion, thrust profile curves, coupled rotational-translational kinematics, atmospheric turbulence, MEMS IMU sensor noise, and Low-Pass Filtering (LPF).

---

## 📊 Telemetry & GNC Dashboard

![GNC Simulation Dashboard](gnc_simulation_dashboard.png)

---

## 🔑 Key Engineering Features

- **Coupled 6-DOF Flight Kinematics:** Translates body-frame thrust vector to inertial frame using real-time orientation ($\theta_y$ pitch angle).
- **Dynamic Mass & Center of Gravity ($CG$) Shift:** Implements linear interpolation (LERP) for continuous $CG$ movement as propellant burns out, dynamically updating torque arms (r(t) = z_{CP} - z_{CG}(t)$).
- **Solid Rocket Motor Model:** Half-sine thrust curve profile (F_{max} \cdot \sin(\pi \cdot t / t_{burn})$) transitioning to ballistic coast flight after burnout.
- **Atmosferic Wind & Turbulence (Gust):** Height-dependent linear base wind speed ($F_0 + k \cdot z$) layered with stochastic low-frequency wind turbulence.
- **IMU Sensor Noise Modeling:** Adds Gaussian (White) noise to real accelerations and angular velocities to simulate realistic hardware sensor measurements.
- **Low-Pass Filter (LPF) Signal Processing:** Sinks raw noisy sensor data to produce clean state estimates for numerical velocity/position integration.
- **Launch Rail Constraint:** Zero-velocity ground lock state preventing early launch until thrust overcomes total gravity weight ($F_{thrust\_z} > m \cdot g$).

---

## 🛠️ Tech Stack & Architecture

- **Core Simulation Engine:** C++ (OOP, System Architecture, Physics Integrator)
- **Data Pipeline & File I/O:** C++ (`std::fstream` exporting structured `.csv` logs)
- **Data Analysis & Visualization:** Python 3 (`pandas`, `matplotlib`)
- **OS/Environment:** Linux (Ubuntu / WSL) & Cross-Platform C++

---

## 📁 Repository Structure

```text
.
├── include/              # C++ Header files (State, Vector3, DataPipeline)
├── src/                  # C++ Source files (Physics engine, Sensor models)
├── main.cpp              # Entry point for simulation loop
├── plot_simulation.py    # Python GNC visualizer dashboard script
├── simulation_output.csv # Generated simulation telemetry log
├── gnc_simulation_dashboard.png # Output visualization graph
└── README.md             # Project documentation