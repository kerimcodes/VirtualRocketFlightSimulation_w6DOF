#include "DataPipeline.h"
#include "VectorOperation.h"
#include "VectorLA.h"
#include <random>
#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>

const std::string path = "data/simulation_output.csv";

void startSimulation(double dt)
{
    createData(dt);
}

void addtoFile(const std::string& path,const std::vector<State>& rawData,const std::vector<State>& measuredData,const std::vector<State>& filteredData,double time_period)
{
    std::ofstream file(path);
    if (file.is_open())
    {   
        file << "Time,"
         << "Real_Acc_X,Real_Acc_Y,Real_Acc_Z,"
         << "Meas_Acc_X,Meas_Acc_Y,Meas_Acc_Z,"
         << "Filt_Acc_X,Filt_Acc_Y,Filt_Acc_Z,"
         << "Real_Vel_X,Real_Vel_Y,Real_Vel_Z,"
         << "Meas_Vel_X,Meas_Vel_Y,Meas_Vel_Z,"
         << "Filt_Vel_X,Filt_Vel_Y,Filt_Vel_Z,"
         << "Real_Pos_X,Real_Pos_Y,Real_Pos_Z,"
         << "Meas_Pos_X,Meas_Pos_Y,Meas_Pos_Z,"
         << "Filt_Pos_X,Filt_Pos_Y,Filt_Pos_Z,"
         << "Real_AngAcc_X,Real_AngAcc_Y,Real_AngAcc_Z,"
         << "Meas_AngAcc_X,Meas_AngAcc_Y,Meas_AngAcc_Z,"
         << "Filt_AngAcc_X,Filt_AngAcc_Y,Filt_AngAcc_Z,"
         << "Real_AngVel_X,Real_AngVel_Y,Real_AngVel_Z,"
         << "Meas_AngVel_X,Meas_AngVel_Y,Meas_AngVel_Z,"
         << "Filt_AngVel_X,Filt_AngVel_Y,Filt_AngVel_Z,"
         << "Real_Theta_X,Real_Theta_Y,Real_Theta_Z,"
         << "Meas_Theta_X,Meas_Theta_Y,Meas_Theta_Z,"
         << "Filt_Theta_X,Filt_Theta_Y,Filt_Theta_Z\n";
        for (int i = 0; i < rawData.size(); i++)
        {
            file << i*time_period << "," << rawData[i].get_A().getX() << "," << rawData[i].get_A().getY() << "," << rawData[i].get_A().getZ() << ","
                 << measuredData[i].get_A().getX() << "," << measuredData[i].get_A().getY() << "," << measuredData[i].get_A().getZ() << ","
                 << filteredData[i].get_A().getX() << "," << filteredData[i].get_A().getY() << "," << filteredData[i].get_A().getZ() << ","
                 << rawData[i].get_V().getX() << "," << rawData[i].get_V().getY() << "," << rawData[i].get_V().getZ() << ","
                 << measuredData[i].get_V().getX() << "," << measuredData[i].get_V().getY() << "," << measuredData[i].get_V().getZ() << ","
                 << filteredData[i].get_V().getX() << "," << filteredData[i].get_V().getY() << "," << filteredData[i].get_V().getZ() << ","
                 << rawData[i].get_P().getX() << "," << rawData[i].get_P().getY() << "," << rawData[i].get_P().getZ() << ","
                 << measuredData[i].get_P().getX() << "," << measuredData[i].get_P().getY() << "," << measuredData[i].get_P().getZ() << ","
                 << filteredData[i].get_P().getX() << "," << filteredData[i].get_P().getY() << "," << filteredData[i].get_P().getZ() << ","
                 << rawData[i].get_AngularA().getX() << "," << rawData[i].get_AngularA().getY() << "," << rawData[i].get_AngularA().getZ() << ","
                 << measuredData[i].get_AngularA().getX() << "," << measuredData[i].get_AngularA().getY() << "," << measuredData[i].get_AngularA().getZ() << ","
                 << filteredData[i].get_AngularA().getX() << "," << filteredData[i].get_AngularA().getY() << "," << filteredData[i].get_AngularA().getZ() << ","
                 << rawData[i].get_AngularV().getX() << "," << rawData[i].get_AngularV().getY() << "," << rawData[i].get_AngularV().getZ() << ","
                 << measuredData[i].get_AngularV().getX() << "," << measuredData[i].get_AngularV().getY() << "," << measuredData[i].get_AngularV().getZ() << ","
                 << filteredData[i].get_AngularV().getX() << "," << filteredData[i].get_AngularV().getY() << "," << filteredData[i].get_AngularV().getZ() << ","
                 << rawData[i].get_theta().getX() << "," << rawData[i].get_theta().getY() << "," << rawData[i].get_theta().getZ() << ","
                 << measuredData[i].get_theta().getX() << "," << measuredData[i].get_theta().getY() << "," << measuredData[i].get_theta().getZ() << ","
                 << filteredData[i].get_theta().getX() << "," << filteredData[i].get_theta().getY() << "," << filteredData[i].get_theta().getZ() << "\n";
        }
        std::cout << "Successful\n";
    }
    else 
        std::cout << "There is no file\n";
}

void applyLowPassFilter(const State &measuredData, State &filteredData,double dt)
{
    const double alfa = 0.05;

    // we first take the unfiltered data
    Vector3 prevfiltered_acc = filteredData.get_A();
    Vector3 prevfiltered_v = filteredData.get_V();
    Vector3 prevfiltered_p = filteredData.get_P();
    Vector3 prevfiltered_angularV = filteredData.get_AngularV();
    Vector3 prevfiltered_angularP = filteredData.get_theta();

    //after that we filtered
    Vector3 filtered_acc = alfa * measuredData.get_A() + (1 - alfa) * prevfiltered_acc;
    Vector3 filtered_angularV = alfa * measuredData.get_AngularV() + (1 - alfa) * prevfiltered_angularV;
    Vector3 filtered_v = prevfiltered_v + filtered_acc * dt;
    Vector3 filtered_p = prevfiltered_p + filtered_v * dt;
    Vector3 filtered_theta = prevfiltered_angularP + filtered_angularV * dt;

    filteredData.set_A(filtered_acc);
    filteredData.set_V(filtered_v);
    filteredData.set_P(filtered_p);
    filteredData.set_AngularV(filtered_angularV);
    filteredData.set_theta(filtered_theta);
}

void createData(double time_period)
{
    const double constant_wind = 0.05, I = 75; // I is moment of inertia
    const double fullMass = 50; 
    double currentMass = 50;
    const double dryMass = 20, mDot = 2;
    const double Fmax = 5000;
    const double position_cgravityfull = 1.0, position_cgravitydry = 1.6; // center gravity when rocket full and dry
    const double burntime = 30 / mDot; // total fuel 30 kg
    const double windF0 = 20;

    const double rho = 1.225;       // kg/m^3 (Air density at sea level)
    const double Cd = 0.45;         // Rocket drag coefficient
    const double radius = 0.075;    //Rocket radius 
    const double S = M_PI * radius * radius; // Cross-sectional area (m²)
    const double Kdamp = 40.0;     // Air damping coefficient that slows down rotation
    const double Krestore = 150.0;  // The lift-to-drag ratio of the ailerons


    const Vector3 g(0, 0, -9.81); // g acc
    std::vector<State> rawData;
    std::vector<State> measuredData;
    std::vector<State> filteredData;
    rawData.reserve(10001); // we reserved for probably 10001 datas 
    measuredData.reserve(10001);
    filteredData.reserve(10001);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> noisy_A(-1.0, 1.0);
    std::uniform_real_distribution<double> noisy_ang(-0.05,0.05);
    std::uniform_real_distribution<double> noisy_w(-5.0, 5.0);
    State initial;
    rawData.emplace_back(initial);
    measuredData.emplace_back(initial);
    filteredData.emplace_back(initial);

    double c_gravity;
    Vector3 r;
    double noisywind = 0.0;

    bool has_taken_off = false;
    int step = 0;
    while (true)
    {
        step++;
        if (step*time_period > 300.0) 
        {
            std::cout << "Warning: Maximum simulation time reached!\n";
            break;
        }

        Vector3 noisy_acc(noisy_A(gen), noisy_A(gen), (noisy_A(gen)));
        Vector3 noisy_angularV(noisy_ang(gen), noisy_ang(gen), noisy_ang(gen));
        noisywind = (noisywind * 0.9) + (noisy_w(gen) * 0.1);

        currentMass -= time_period * mDot;
        if (currentMass > dryMass)
            // center gravity based on time
            c_gravity = position_cgravitydry + ((currentMass - dryMass) / (fullMass - dryMass)) * (position_cgravityfull - position_cgravitydry);
        else
            {
                c_gravity = position_cgravitydry;
                currentMass = dryMass;
            }

        Vector3 Fwind(windF0 + constant_wind * filteredData[step-1].get_P().getZ() + noisywind, 0, 0);
        r.setZ(position_cgravityfull-c_gravity);
        
        Vector3 V_rel = rawData[step-1].get_V(); // velocity of rocket
        double V_mag = length(V_rel);           // velocity length |V|

        Vector3 F_drag(0, 0, 0);
        if (V_mag > 1e-5) {
            // F_drag = -0.5 * rho * Cd * S * |V| * V_vec
            F_drag = V_rel * (-0.5 * rho * Cd * S * V_mag);
        }

        double F_thrust_mag = 0.0;
        if (step*time_period <= burntime) 
            F_thrust_mag = Fmax * std::sin(M_PI * step*time_period / burntime); 
        else 
            F_thrust_mag = 0.0; 

        double pitch = rawData[step-1].get_theta().getY();
        double F_thrust_x = F_thrust_mag * std::sin(pitch);
        double F_thrust_y = 0.0; 
        double F_thrust_z = F_thrust_mag * std::cos(pitch);

        Vector3 F_thrust(F_thrust_x, F_thrust_y, F_thrust_z);
        Vector3 force = F_thrust + F_drag + Fwind +  currentMass * g;
        
        if (rawData[step-1].get_P().getZ() <= 0.0 && force.getZ() <= 0.0) 
            force = Vector3(0.0, 0.0, 0.0); 

        Vector3 wind_torque = crossproduct(r, Fwind);
        Vector3 damping_torque = rawData[step-1].get_AngularV() * (-Kdamp);
        // Aileron up-torque (Counter-torque against roll)
        Vector3 restoring_torque = rawData[step-1].get_theta() * (-Krestore);
        // Total Net Torque
        Vector3 torque = wind_torque + damping_torque + restoring_torque;

        // x = x0 + v*t and v = v0 a*t;
        Vector3 raw_acc = force / currentMass;
        Vector3 raw_v = rawData[step-1].get_V() + raw_acc * time_period;
        Vector3 raw_p = rawData[step-1].get_P() + raw_v * time_period;
        if (raw_p.getZ() > 0)
            has_taken_off = true;

        if (has_taken_off && raw_p.getZ() <= 0)
        {
            Vector3 final_p(raw_p.getX(), raw_p.getY(), 0.0);
            Vector3 stop(0.0, 0.0, 0.0);
            Vector3 final_theta = rawData.back().get_theta();

            State landed_state(final_p, stop, stop, final_theta, stop, stop);

            rawData.emplace_back(landed_state);
            measuredData.emplace_back(landed_state);
            filteredData.emplace_back(landed_state);
            break;
        }

        Vector3 raw_angularAcc = torque / I;
        Vector3 raw_angularV = rawData[step-1].get_AngularV() + raw_angularAcc * time_period;
        Vector3 raw_angularP = rawData[step-1].get_theta() + raw_angularV * time_period;
        State raw(raw_p, raw_v, raw_acc, raw_angularP, raw_angularV, raw_angularAcc);
        rawData.emplace_back(raw);

        Vector3 measured_acc = raw_acc + noisy_acc;
        Vector3 measured_v = measuredData[step-1].get_V() + measured_acc * time_period;
        Vector3 measured_p = measuredData[step-1].get_P() + measured_v * time_period;
        Vector3 measured_angularV = raw_angularV + noisy_angularV;
        Vector3 measured_angularP = measuredData[step-1].get_theta() + measured_angularV * time_period;
        State measured(measured_p, measured_v, measured_acc, measured_angularP, measured_angularV, raw_angularAcc);
        measuredData.emplace_back(measured);

        filteredData.emplace_back(filteredData[step-1]);
        applyLowPassFilter(measuredData[step], filteredData[step],time_period);   
    }
    addtoFile(path, rawData, measuredData, filteredData,time_period);
}