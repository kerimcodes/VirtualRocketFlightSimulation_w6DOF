#pragma once
#include "State.h"
#include <string>
#include <vector>

void createData(double dt, int loop);
void applyLowPassFilter(const State & measuredData,State& filteredData,double dt);
void addtoFile(const std::string &path , const std::vector<State>& rawData,const std::vector<State>& measuredData,const std::vector<State>& filteredData,int loop);

