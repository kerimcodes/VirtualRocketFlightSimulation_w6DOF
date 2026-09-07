# 🚀 6-DOF Rocket SITL Simulation & GNC Sensor Filtering

A **C++ Software-in-the-Loop (SITL) rocket flight simulation** that models 6-degree-of-freedom flight dynamics and generates synthetic telemetry for Python-based analysis and visualization.

The project explores how a simplified rocket model can be combined with **sensor noise, signal processing, and telemetry analysis** to form the foundation of a GNC-oriented simulation workflow.

---

## 🎯 Project Objective

The main objective is to build a modular rocket simulation that connects:

```text
Flight Dynamics
      ↓
Sensor Model
      ↓
Noisy Measurements
      ↓
Signal Filtering
      ↓
Telemetry
      ↓
Python Analysis
```

The simulation is designed as a foundation for future guidance, navigation, and control experiments.

---

## ✈️ Flight Dynamics

The simulation models coupled translational and rotational motion in a 6-DOF framework.

The system includes:

* Translational dynamics
* Rotational dynamics
* Body-to-inertial frame transformations
* Thrust vector effects
* Dynamic mass variation
* Center-of-gravity movement
* Torque generation
* Atmospheric disturbances

---

## 🔥 Propulsion Model

The rocket uses a simplified solid motor thrust model.

The thrust profile is represented using a half-sine function:

$$
F(t) = F_{max}
\sin\left(\frac{\pi t}{t_{burn}}\right)
$$

After the burn phase ends, the vehicle transitions to ballistic flight.

This model is intentionally simplified and is primarily used to study the interaction between propulsion, vehicle dynamics, and estimation.

---

## ⚖️ Dynamic Mass & Center of Gravity

As propellant is consumed:

```text
Propellant depletion
        ↓
Total mass changes
        ↓
CG location changes
        ↓
Moment arm changes
        ↓
Rotational dynamics change
```

The simulation updates the center of gravity continuously during flight.

This allows the model to represent one of the important time-varying properties of a rocket vehicle.

---

## 🌬️ Wind & Atmospheric Disturbances

The simulation includes a simplified atmospheric disturbance model containing:

* Height-dependent base wind
* Low-frequency stochastic turbulence
* Gust effects

These disturbances introduce variability into the simulated flight trajectory and sensor measurements.

---

## 📡 IMU Sensor Model

The simulation does not directly expose perfect ground-truth states as sensor measurements.

Instead, sensor noise is added to simulated accelerations and angular velocities to approximate realistic MEMS IMU behavior.

Conceptually:

```text
True State
    ↓
Vehicle Dynamics
    ↓
True Acceleration / Angular Velocity
    ↓
Sensor Noise
    ↓
Simulated IMU Output
```

Gaussian noise is used as a simplified sensor-noise model.

---

## 🔎 Low-Pass Filtering

The noisy IMU measurements are processed using a Low-Pass Filter (LPF).

```text
Raw Sensor
     │
     ▼
Noisy Measurement
     │
     ▼
    LPF
     │
     ▼
Filtered Signal
```

The filtered measurements can then be used for numerical integration and downstream state estimation experiments.

---

## 🚦 Launch Rail Constraint

A simplified launch-rail constraint is included to prevent the vehicle from immediately entering free flight.

The model keeps the vehicle constrained until the thrust condition required for launch is satisfied.

This provides a more realistic transition between:

```text
Ground Constraint
       ↓
Launch
       ↓
Powered Flight
       ↓
Burnout
       ↓
Ballistic Flight
```

---

## 📊 Telemetry Pipeline

Simulation data is exported to CSV and analyzed using Python.

```text
C++ Simulation
      │
      ▼
Telemetry CSV
      │
      ▼
Python
      │
 ┌────┴─────┐
 ▼          ▼
Pandas   Matplotlib
 │          │
 └────┬─────┘
      ▼
Visualization
```

The Python side is used for:

* Telemetry inspection
* Signal visualization
* Sensor/filter comparison
* Flight-data analysis

---

## 🧩 Software Architecture

```text
.
├── header/
│   └── C++ header files
│
├── source/
│   └── Physics and sensor implementation
│
├── main.cpp
│   └── Simulation entry point
│
├── visualise/
│   └── Python telemetry analysis
│
├── .gitignore
└── README.md
```

---

## 🛠️ Technology Stack

### Simulation

* C++
* Object-Oriented Programming
* Numerical integration
* Physics modeling
* CSV telemetry generation

### GNC / Data Processing

* Python
* Pandas
* Matplotlib
* Signal filtering

### Environment

* Linux / Ubuntu
* WSL
* Cross-platform C++

---

## 🧠 Engineering Concepts Explored

This project combines several areas that are relevant to aerospace simulation and GNC:

* 6-DOF dynamics
* Coordinate transformations
* Mass depletion
* Center-of-gravity variation
* Thrust modeling
* Disturbance modeling
* Sensor noise
* Digital filtering
* Telemetry generation
* Numerical simulation
* Python-based data analysis

---

## 🔮 Future Development

Possible next steps include:

### Navigation

* IMU bias modeling
* Sensor bias estimation
* State estimation
* Kalman filtering

### Guidance

* Reference trajectory generation
* Target tracking
* Guidance-law experiments

### Control

* Attitude control
* Rate control
* PID / PD control
* State-space control
* Controller-in-the-loop experiments

### Simulation

* More complete 6-DOF equations
* Improved aerodynamic modeling
* Higher-fidelity atmosphere
* Better numerical integration
* Simulation validation against analytical cases

---

## 📌 Project Status

**Experimental / Educational SITL**

The current implementation focuses on building a modular simulation and sensor-processing foundation rather than a flight-certified or high-fidelity aerospace simulator.

---

## 📚 Related Topics

`C++` `Aerospace` `Rocket Simulation` `6-DOF` `Flight Dynamics` `SITL` `GNC` `IMU` `Sensor Fusion` `Signal Processing` `Telemetry` `Numerical Simulation`
