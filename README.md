# 6-DOF Rocket Flight Simulation

A C++-based 6-DOF rocket flight simulation project focused on rigid-body dynamics, changing mass properties, sensor modeling, telemetry generation, and post-flight data analysis.

The project is intended as a simulation foundation for future **Guidance, Navigation & Control (GNC)** development.

---

## 🚀 Project Overview

The simulator models the motion of a rocket in six degrees of freedom:

### Translational Motion

* Position
* Velocity
* Acceleration

### Rotational Motion

* Attitude
* Angular velocity
* Rotational dynamics

The simulation also accounts for several non-ideal physical and sensor effects.

---

## 🧮 Dynamics Model

The simulation includes:

* 6-DOF rigid-body dynamics
* Variable mass
* Center-of-gravity variation
* Thrust profile
* Gravity
* Aerodynamic/environmental effects
* Atmospheric wind/turbulence effects

Changing mass properties are incorporated throughout the flight rather than assuming a constant vehicle mass.

---

## 📡 Sensor Modeling

The simulator includes an IMU-oriented sensor model with effects such as:

* Measurement noise
* Bias
* Filtering

A low-pass filtering stage is used to process simulated measurements before telemetry analysis.

---

## 📊 Telemetry & Visualization

Simulation data is exported for post-processing and visualization.

Python is used for:

* Telemetry analysis
* Plotting
* Flight-data visualization
* Inspecting simulated system behavior

This separation keeps the core flight-dynamics simulation in C++ while using Python for analysis and visualization.

---

## 🏗️ Project Structure

```text
.
├── header/
├── source/
├── visualise/
└── README.md
```

The project separates declarations, implementations, and visualization/analysis components to keep the codebase modular.

---

## 🔄 Simulation Pipeline

```text
        Rocket Parameters
               │
               ▼
       6-DOF Dynamics Model
               │
       ┌───────┴────────┐
       │                │
       ▼                ▼
 Translational       Rotational
   Dynamics            Dynamics
       │                │
       └───────┬────────┘
               ▼
          Sensor Model
               │
               ▼
           Filtering
               │
               ▼
           Telemetry
               │
               ▼
       Python Visualization
```

---

## 🎯 Motivation

The long-term goal of this project is to evolve the simulator into a complete GNC development environment.

The current simulation provides the dynamics and sensor-modeling foundation required for future work in:

* State estimation
* Sensor fusion
* Guidance
* Feedback control
* Actuator modeling
* Autonomous flight

---

## 🔮 Planned Development

Future development is planned around:

### Navigation

* Kalman Filter
* Extended Kalman Filter
* IMU/GPS sensor fusion
* Attitude estimation

### Control

* State-space modeling
* LQR
* Optimal control
* MPC

### GNC

```text
Guidance
    ↓
Navigation / State Estimation
    ↓
Control
    ↓
Actuator Model
    ↓
6-DOF Rocket Dynamics
    ↓
Sensor Model
    └───────────────↺
```

The goal is to gradually transform the current flight simulator into a complete closed-loop GNC simulation platform.

---

## 🛠️ Technologies

### Core Simulation

* C++
* 6-DOF Dynamics
* Numerical Simulation

### Data Analysis

* Python
* NumPy
* Matplotlib

### Concepts

* Rigid-body dynamics
* Flight simulation
* Sensor modeling
* Filtering
* Telemetry
* GNC

---

## 📌 Project Status

The current version focuses primarily on **flight dynamics, sensor modeling, filtering, and telemetry**.

GNC algorithms such as EKF, LQR, and MPC are planned future extensions rather than part of the current implementation.
