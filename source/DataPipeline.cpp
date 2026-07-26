#include "DataPipeline.h"
#include "VectorOperation.h"
#include "VectorLA.h"
#include <random>
#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>

const std::string path = "data/simulation_output.csv";

void addtoFile(const std::string& path,const std::vector<State>& rawData,const std::vector<State>& measuredData,const std::vector<State>& filteredData,int loop)
{
    std::fstream file(path);
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
        for (int i = 0; i <= loop; i++)
        {
            file << i*(0.01) << "," << rawData[i].get_A().getX() << "," << rawData[i].get_A().getY() << "," << rawData[i].get_A().getZ() << ","
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

    Vector3 prevfiltered_acc = filteredData.get_A();
    Vector3 prevfiltered_v = filteredData.get_V();
    Vector3 prevfiltered_p = filteredData.get_P();
    Vector3 prevfiltered_angularV = filteredData.get_AngularV();
    Vector3 prevfiltered_angularP = filteredData.get_theta();

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

void createData(double time_period, int loop)
{
    const double constant_wind = 0.05, I = 75;
    const double fullMass = 50;
    double currentMass = 50;
    const double dryMass = 20, mDot = 2;
    const double Fmax = 5000;
    const double position_cgravityfull = 1.0, position_cgravitydry = 1.6;
    const double burntime = 30 / mDot;
    const double windF0 = 20;
    const Vector3 g(0, 0, -9.81);

    std::vector<State> rawData;
    std::vector<State> measuredData;
    std::vector<State> filteredData;
    rawData.reserve(loop + 1);
    measuredData.reserve(loop + 1);
    filteredData.reserve(loop + 1);

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
    for (int i = 1; i <= loop; i++)
    {   
        Vector3 noisy_acc(noisy_A(gen), noisy_A(gen), (noisy_A(gen)));
        Vector3 noisy_angularV(noisy_ang(gen), noisy_ang(gen), noisy_ang(gen));
        noisywind = (noisywind * 0.9) + (noisy_w(gen) * 0.1);

        currentMass -= time_period * mDot;
        if (currentMass > dryMass)
            c_gravity = position_cgravitydry + ((currentMass - dryMass) / (fullMass - dryMass)) * (position_cgravityfull - position_cgravitydry);
        else
            c_gravity = position_cgravitydry;   

        Vector3 Fwind(windF0 + constant_wind * filteredData[i-1].get_P().getZ() + noisywind, 0, 0);
        r.setZ(position_cgravityfull-c_gravity);

        double F_thrust_mag = 0.0;
        if (i*time_period <= burntime) 
            F_thrust_mag = Fmax * std::sin(M_PI * i*time_period / burntime); 
        else 
            F_thrust_mag = 0.0; 


        double pitch = rawData[i - 1].get_theta().getY();
        double F_thrust_x = F_thrust_mag * std::sin(pitch);
        double F_thrust_y = 0.0; 
        double F_thrust_z = F_thrust_mag * std::cos(pitch);

        Vector3 F_thrust(F_thrust_x, F_thrust_y, F_thrust_z);

        Vector3 force = F_thrust + Fwind +  currentMass * g;
        
        if (rawData[i - 1].get_P().getZ() <= 0.0 && force.getZ() <= 0.0) 
            force = Vector3(0.0, 0.0, 0.0); 

        Vector3 torque = crossproduct(r, Fwind);

        Vector3 raw_acc = force / currentMass;
        Vector3 raw_v = rawData[i - 1].get_V() + raw_acc * time_period;
        Vector3 raw_p = rawData[i - 1].get_P() + raw_v * time_period;
        Vector3 raw_angularAcc = torque / I;
        Vector3 raw_angularV = rawData[i - 1].get_AngularV() + raw_angularAcc * time_period;
        Vector3 raw_angularP = rawData[i - 1].get_theta() + raw_angularV * time_period;
        State raw(raw_p, raw_v, raw_acc, raw_angularP, raw_angularV, raw_angularAcc);
        rawData.emplace_back(raw);

        Vector3 measured_acc = raw_acc + noisy_acc;
        Vector3 measured_v = measuredData[i - 1].get_V() + measured_acc * time_period;
        Vector3 measured_p = measuredData[i - 1].get_P() + measured_v * time_period;
        Vector3 measured_angularV = raw_angularV + noisy_angularV;
        Vector3 measured_angularP = measuredData[i - 1].get_theta() + measured_angularV * time_period;
        State measured(measured_p, measured_v, measured_acc, measured_angularP, measured_angularV, measured_acc);
        measuredData.emplace_back(measured);

        filteredData.emplace_back(filteredData[i-1]);
        applyLowPassFilter(measuredData[i], filteredData[i],time_period);   
    }
    addtoFile(path, rawData, measuredData, filteredData, loop);
}