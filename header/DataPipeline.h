#pragma once
#include "State.h"
#include <string>
#include <vector>

void startSimulation(double dt);
void createData(double dt);
void applyLowPassFilter(const State & measuredData,State& filteredData,double dt);
void addtoFile(const std::string &path , const std::vector<State>& rawData,const std::vector<State>& measuredData,const std::vector<State>& filteredData,double time_period);

